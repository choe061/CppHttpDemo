//
//  Car.cpp
//  CppProject
//
//  Created by choi on 2018. 3. 20..
//  Copyright © 2018년 choi. All rights reserved.
//

#include <iostream>
#include <cstring>
#include "Car.h"

using namespace std;

Car::Car()
{
    strcpy(this->gamerID, "Anonymous");
    this->fuelGauge = 100;
    this->carSpeed = 0;
}

Car::Car(char *id, int fuel)
{
    strcpy(this->gamerID, id);
    this->fuelGauge = fuel;
    this->carSpeed = 0;
}

void Car::initMembers(char* id, int fuel)
{
    strcpy(gamerID, id);
    fuelGauge = fuel;
    carSpeed = 0;
}

void Car::showCarState()
{
    cout << "-------차량 상태-------" << endl;
    cout << "소유자 아이디 : " << gamerID << endl;
    cout << "연료량 : " << fuelGauge << "%" << endl;
    cout << "현재 속도 : " << carSpeed << "km/s" << endl;
}

void Car::accel()
{
    if (fuelGauge <= 0) {
        return;
    } else {
        fuelGauge -= CAR_CONST::FUEL_STEP;
    }
    
    if ((carSpeed += CAR_CONST::ACC_STEP) >= CAR_CONST::MAX_SPEED) {
        carSpeed = CAR_CONST::MAX_SPEED;
    }
//    carSpeed += CAR_CONST::ACC_STEP;
}

void Car::breakCar()
{
    if ((carSpeed -= CAR_CONST::BRK_STEP) < CAR_CONST::BRK_STEP) {
        carSpeed = 0;
        return ;
    }
}
