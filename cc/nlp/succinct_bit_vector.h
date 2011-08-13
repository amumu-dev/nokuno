unsigned long long PopCount64(unsigned long long x) {
  x = ((x & 0xaaaaaaaaaaaaaaaaULL) >> 1)
      +  (x & 0x5555555555555555ULL);
  x = ((x & 0xccccccccccccccccULL) >> 2)
      +  (x & 0x3333333333333333ULL);
  x = ((x & 0xf0f0f0f0f0f0f0f0ULL) >> 4)
      +  (x & 0x0f0f0f0f0f0f0f0fULL);
  x = ((x & 0xff00ff00ff00ff00ULL) >> 8)
      +  (x & 0x00ff00ff00ff00ffULL);
  x = ((x & 0xffff0000ffff0000ULL) >> 16)
      +  (x & 0x0000ffff0000ffffULL);
  x = ((x & 0xffffffff00000000ULL) >> 32)
      +  (x & 0x00000000ffffffffULL);
  return x;
}

class SuccinctBitVector {
 private:
  unsigned long long bit_vector[4];
  unsigned char  rank_array[4];

 public:
  SuccinctBitVector() {
    for (int i = 0; i < 4; i++) {
      this->bit_vector[i] = 0x0ULL;
      this->rank_array[i] = 0;
    }
  }
  void Set(int i) {
    unsigned long long b = 0x1ULL << (i % 64);
    this->bit_vector[i / 64] |= b;
  }
  bool Get(int i) const {
    unsigned long long m = 0x1ULL << (i % 64);
    return this->bit_vector[i / 64] & m;
  }
  void Build() {
    this->rank_array[0] = 0;
    for (int i = 0; i < 3; i++) {
      this->rank_array[i + 1] = this->rank_array[i] + PopCount64(this->bit_vector[i]);
    }
  }
  int Rank(int i) const {
    unsigned long long m = (0x1ULL << (i % 64 + 1)) - 1;
    return this->rank_array[i / 64] + PopCount64(this->bit_vector[i / 64] & m);
  }

};

