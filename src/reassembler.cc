#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{

  //到达末尾
  if(is_last_substring){
    lastpos = first_index + data.size();
  }

  //超出窗口
  if(first_index >= nread + output.available_capacity() || first_index + data.size() < nread){
    return;
  }

  //左侧溢出
  if(first_index < nread){
    data = data.substr(nread - first_index);
    first_index = nread;
  }

  //右侧溢出
  if(first_index + data.size() > nread + output.available_capacity() - first_index){
    data = data.substr(0, nread + output.available_capacity() - first_index);
  }

  //循环写入flag填充标志位
  while(box.size() < first_index + data.size()){
    box.push_back(flag);
  }

  for(auto &ch : data){
    if(box[first_index] == flag){
      box[first_index] = ch;
      store++;
    }
    first_index++;
  }

  string buffer;
  while( nread < box.size() && box[nread] != flag){
    buffer += (char)box[nread++];
    store--;
  }

  if(!buffer.empty()){
    output.push(buffer);
  }

  if(nread >= lastpos){
    output.close();
  }

  // Your code here.
  // (void)first_index;
  // (void)data;
  // (void)is_last_substring;
  // (void)output;
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return store;
}
