#include "tcp_receiver.hh"

using namespace std;

//1. 从对等方的发送方接收消息，并使用reassembler重新组装字节流
//2. 将包含确认号和窗口大小的消息发送回对等方的发送方


void TCPReceiver::receive( TCPSenderMessage message, Reassembler& reassembler, Writer& inbound_stream )
{
  // Your code here.
  // (void)message;
  // (void)reassembler;
  // (void)inbound_stream;

  //是否有接收消息
  if(message.SYN){
    SYN_Received = true;
    zero_point = message.seqno;
  }

  //不接收就返回
  if(!SYN_Received){
    return;
  }


  //用reassembler重新组装字节流
  // uint64_t first_index, string data, bool is_last_substring, Writer& output
  reassembler.insert(
    //绝对序列号转换成流索引
    //绝对序列号包含SYN和FIN，需要加上SYN再减一
    message.seqno.unwrap(zero_point, inbound_stream.bytes_pushed()) + message.SYN - 1,
    string(message.payload),
    message.FIN,
    inbound_stream
  );
}

TCPReceiverMessage TCPReceiver::send( const Writer& inbound_stream ) const
{
  // Your code here.
  // (void)inbound_stream;
  TCPReceiverMessage tcprmsg;
  //序列号+SYN+FIN
  if(SYN_Received){
    tcprmsg.ackno = help.wrap(inbound_stream.bytes_pushed() + inbound_stream.is_closed() + 1, zero_point);
  }

  //ack之后剩余的为窗口大小
  uint64_t res = inbound_stream.available_capacity();
  //最大容量为UINT16_MAX
  tcprmsg.window_size = res > UINT16_MAX ? UINT16_MAX : res;
  return {tcprmsg};

}
