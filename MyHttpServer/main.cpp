//
//  main.cpp
//  CppProject
//
//  Created by choi on 2018. 3. 20..
//  Copyright © 2018년 choi. All rights reserved.
//

#include <iostream>
#include "Car.h"

using namespace std;

struct Player
{
    char *name = "choe";
    int level = 10;
};

int main(int argc, const char * argv[]) {
    // 구조체에서 -> 와 같은 포인터 요소로 선택
    Player *player = new Player;    //구조체를 동적 할당
    player->name = "beomgyun";
    cout << player->name << ", " << player->level << endl;
    
    // insert code here...
    // 클래스 객체는 . 과 같은 참조로 요소 선택
    Car run99("run99", 100);
//    run99.initMembers("run99", 100);
    
    run99.accel();
    run99.accel();
    run99.accel();
    run99.showCarState();
    run99.breakCar();
    run99.showCarState();
    run99.accel();
    run99.showCarState();
    return 0;
}
