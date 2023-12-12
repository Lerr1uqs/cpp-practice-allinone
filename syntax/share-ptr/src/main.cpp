#include <iostream>
#include <cstdint>
#include <cassert>

using namespace std;
#define fn auto
#define self (*this)
#define u32 uint32_t
#define i32 int32_t

class RefCount {
  public:
    RefCount(): inner_count(1) {}
    fn increase() -> void {
        self.inner_count += 1;
    }
    fn decrease() -> void {
        self.inner_count -= 1;
    }
    fn count() -> u32 {
        return self.inner_count;
    };
    fn count(u32 xcount) -> void {
        self.inner_count = xcount;
    };
  private:
    u32 inner_count;
};

template<class T>
class SharePtr {
  public:// TODO: 两种初始化方式
    SharePtr(T *xptr = nullptr): ptr(xptr) {
        if(xptr) {
            self.inner_rc = new RefCount;// 多个智能指针共享一个 rc指针
        }
    }
    ~SharePtr() {
        if(self.inner_rc->count() == 0) {
            return;
        }

        if(self.inner_rc->count() == 1) {
            self.inner_rc->count(0);

            delete self.ptr;     self.ptr      = nullptr;
            delete self.inner_rc;self.inner_rc = nullptr;
        }else {
            self.inner_rc->decrease();
        }

    }
    SharePtr(const SharePtr &other) {
        self.ptr = other.ptr;
        if(self.ptr) {
            other.inner_rc->increase();
            self.inner_rc = other.inner_rc;
        }
    }
    fn operator =(const SharePtr &other) -> SharePtr& {
        self.ptr = other.ptr;
        if(self.ptr) {
            other.inner_rc->increase();
            self.inner_rc = other.inner_rc;
        }
        return self;
    }
    fn rc() -> u32 {
        return self.inner_rc->count();
    }
  private:
    T *ptr;
    RefCount *inner_rc;
};

#define banner cout << "-----------------" << endl;

int main(int argc, char** argv)
{
    SharePtr<int>p0(new int{1});
    SharePtr<int>p1(p0);
    SharePtr<int>p2 = p1;

    assert(p0.rc() == p1.rc());
    assert(p1.rc() == p2.rc());
    assert(p1.rc() == 3);

    
    return 0;
}
