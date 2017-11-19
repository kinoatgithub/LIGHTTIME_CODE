#ifndef __CONFIG_H_
#define __CONFIG_H_

#define ONE_PULSE_WIDTH						10				//单脉冲走时模式，脉冲持续时间,定性，多减少加。
#define DELAY_UNIT							10				//*次某运算作为延时的最小时间间隔，定性，多减少加。
#define ANGULAR_ACCELERATION_RATE			99				//角加速度
#define ANTI_JAGGIES						100				//角加速抗锯齿化，提高分辨率
#define DELAY_INITIAL_VALUE					10000			//加速旋转时首次延时时间
#define MIN_DELAY_TIME						10				//高速旋转时最小延时
#define SWITCH_DISCHARGE_PERIOD				80				//设置按键扫描时电容放电持续时间，定性，多减少加。
#define	SWITCH_CHARGE_PERIOD				20				//设置按键扫描时电容充电持续时间，定性，多减少加。
#define SWITCH_HYSTERESIS_VAL               4               //方向回滞，重复确认次数以减少误触发


#endif
