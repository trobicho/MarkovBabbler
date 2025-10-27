#pragma once
#include <istream>
#include <string>
#include <vector>
#include "lex.hpp"

struct Token {
  Token(std::string word): word(word) {};

  std::string       word;
  std::vector<int>  probabilities;
  int               count = 1;
};

class TokenTable {
  public:
    void initTokenTable(Lex& lexer) {
      char           buffer[4096];
      std::string word = "";

      while(lexer.nextToken(word)) {
        addToken(word);
      }
      for(auto& token: m_table) {
        token.probabilities.resize(m_table.size(), 0.0);
      }
      //second pass rewind file sort token alphabetically
      lexer.rewind();

      std::string  words[2] = {""};
      int          w = 0;

      while(lexer.nextToken(words[w])) {
        if (words[w ^ 1] != "") {
          int  id1 = getTokenIndex(words[w]);
          int  id2 = getTokenIndex(words[w^1]);
          if (id1 != -1 && id2 != -1)
            m_table[id1].probabilities[id2] += 1;
        }
        w ^= 1;
      }
      int id = getTokenIndex(words[w]);
      if (id != -1) {
        m_table[id].count -= 1;
      }
    }

    int   size() {return (m_table.size());}

    void  addToken(std::string& word) {
      for (auto& token: m_table) {
        if (token.word == word) {
          token.count += 1;
          return ;
        }
      }
      m_table.push_back(Token(word));
    }

    int   getTokenIndex(std::string& word) {
      for (int i = 0; i < m_table.size(); i++) {
        if (m_table[i].word == word) {
          return (i);
        }
      }
      return (-1);
    }

    std::string babble(int& state) {
      auto& token = m_table[state];
      double dice = (rand() % token.count);

      int total = 0;
      int i;
      int last = 0;
      for (i = 0; i < token.probabilities.size(); i++) {
        total += token.probabilities[i];
        if (token.probabilities[i] > 0)
          last = i;
        if (total > dice)
          break;
      }
      state = last;
      return (m_table[state].word);
    }

  private:
    std::vector<Token>  m_table;
};
