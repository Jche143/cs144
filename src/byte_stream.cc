#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_(capacity), buffer() {}

void Writer::push( string data )
{
  for ( auto& ch : data ) {
    if ( buffer.size() >= capacity_ ) {
      set_error();
      return;
    }
    send++;
    buffer.push(ch);
  }

  // Your code here.
  // (void)data;
}

void Writer::close()
{
  is_close = true;
  // Your code here.
}

void Writer::set_error()
{
  is_error = true;
  // Your code here.
}

bool Writer::is_closed() const
{
  // Your code here.
  return { is_close };
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return { capacity_ - buffer.size() };
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return { send };
}

string_view Reader::peek() const
{
  // Your code here.
  return { std::string_view(&buffer.front(), 1) };
}

bool Reader::is_finished() const
{
  // Your code here.
  return { is_close && buffer.empty() };
}

bool Reader::has_error() const
{
  // Your code here.
  return { is_error };
}

void Reader::pop( uint64_t len )
{
  while ( len > 0 && !( buffer.empty() ) ) {
    buffer.pop();
    len--;
    ++recv;
  }
  // Your code here.
  // (void)len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return { buffer.size() };
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return { recv };
}
