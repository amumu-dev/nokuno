/*
 * =====================================================================================
 *
 *       Filename:  template.cc
 *
 *    Description:  template test of cvim
 *
 *        Version:  1.0
 *        Created:  2010/12/05 13時56分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yoh Okuno (), nokuno@nokuno.jp
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

namespace test {
    class Test {
        public:
            void hello() {
                cout << "Hello, World!" << endl;
            }
    };
}
int main() {
    test::Test obj;
    obj.hello();
    return 0;
}
