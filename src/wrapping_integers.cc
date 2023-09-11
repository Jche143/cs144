#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  //绝对序列号 -> 序列号
  // Your code here.
  // (void)n;
  // (void)zero_point;

  return Wrap32 { zero_point + (uint32_t)(n << 32 >> 32) };
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  // Your code here.
  // (void)zero_point;
  // (void)checkpoint;

  //序列号 -> 绝对序列号

  //计算当前序列号到初始序列号之间的偏移n
  uint64_t offset = raw_value_  - zero_point.raw_value_;
  
  //如果距离小于一个2的32次方
  if ( checkpoint < offset ) {
    return offset;
  }

  //如果距离大于一个2的32次方
  //checkpoint距离小于2的32次方左侧
  uint64_t l = ( ( ( checkpoint - offset ) >> 32 ) << 32 ) + offset;

  //加一个2的32次方到checkpoint右侧距离最近
  uint64_t r = ( ( ( ( checkpoint - offset ) >> 32 ) + 1 ) << 32 ) + offset;

  //比较哪个近
  uint64_t ans = checkpoint - l < r - checkpoint ? l : r;
  
  return { ans };

  // Wrap32 WrapCheckpoint = wrap(checkpoint, zero_point);
  // int32_t diff = res - WrapCheckpoint.raw_value_;

  // if (diff < 0 && diff + checkpoint > checkpoint){
  //   return (uint32_t)diff + checkpoint;
  // }

  // return diff + checkpoint;
}
