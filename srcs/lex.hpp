#pragma once
#include <istream>
#include <string>

class Lex {
  public:
    Lex(std::istream* stream): m_stream(stream) {loadBuffer();}

    int nextToken(std::string& word) {
      word = "";
      while (1) {
        if (m_cur >= m_size) {
          if (m_size == 4096) {
            loadBuffer();
            if (m_size == 0)
              break;
          }
          else
            break;
        }
        if (m_buffer[m_cur] == ' ' && word != "") {
          m_cur++;
          break;
        }
        word += m_buffer[m_cur];
        m_cur++;
      }
      if (word != "")
        return (1);
      return (0);
    }

    void  rewind() {
      m_stream->clear();
      m_stream->seekg(0, m_stream->beg);
      loadBuffer();
    }
    void  loadBuffer() {
      m_stream->read(m_buffer, 4096);
      m_size = m_stream->gcount();
      m_cur = 0;
    }

  private:
    std::istream* m_stream;
    char          m_buffer[4096];
    size_t        m_size = 0;
    int           m_cur = 0;
};
