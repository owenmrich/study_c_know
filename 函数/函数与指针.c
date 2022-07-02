//指针函数 返回值为指针的函数
//  int * fun(int)
//  调用 fun(i)

//函数指针 指向函数的指针，指向的类型要一样
//  int (*fuc) (int a)
//  int add(int)
//  fuc = add;
//  调用 p(i)

//函数指针数组
//  int (*func[N]) (int )
//  int add(int)
//  int sbu(int)
//  func[1] = add;
//  func[2] = sbu;
//  调用 func[1](i)
