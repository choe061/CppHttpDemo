//
//  Car.h
//  CppProject
//
//  Created by choi on 2018. 3. 20..
//  Copyright © 2018년 choi. All rights reserved.
//  파일의 최상단은 주석이 위치할 것
//

#ifndef Car_h
#define Car_h

namespace CAR_CONST
{
    enum {
        ID_LEN = 20,
        MAX_SPEED = 200,
        FUEL_STEP = 2,
        ACC_STEP = 10,
        BRK_STEP = 10
    };
}

class Car {
private:
    char gamerID[CAR_CONST::ID_LEN];
    int fuelGauge;
    int carSpeed;
    
public:
    /**
     *  default constructor
     */
    Car();
    
    /**
     *  @id : 아이디
     *  @fuel : 엔진 상태, 디폴트 값으로 100을 줌
     */
    Car(char *id, int fuel = 100);
    
    /**
     * public 함수에는 주석을 작성하는 것이 좋다. private 함수라면 작성하지 않아도 괜찮다.
     * .h파일에 주석을 작성하던, .cpp파일에 주석을 작성하던 상관없다.
     */
    void initMembers(char* id, int fuel);
    
    /**
     *
     */
    void showCarState();
    
    /**
     *
     */
    void accel();
    
    /**
     *
     */
    void breakCar();
};

#endif /* Car_h */
