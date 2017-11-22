#ifndef __CONFIG_H_
#define __CONFIG_H_

#define ONE_PULSE_FREQ						100					//单脉冲走时模式，脉冲持续时间,定性，多减少加。
#define ANGULAR_ACCELERATION				1000				//用于角加速,值越大加速度越小，定性，多减少加。
#define ANTI_JAGGIES						65535				//角加速抗锯齿化，提高分辨率
#define DELAY_INITIAL_VALUE					1					//加速旋转时首次延时时间
#define FREQ_LIMIT							1000				//高速旋转时最大速度
#define SWITCH_DISCHARGE_PERIOD				5					//设置按键扫描时电容放电持续时间，定性，多减少加。
#define	SWITCH_CHARGE_PERIOD				10					//设置按键扫描时电容充电持续时间，定性，多减少加。
#define SWITCH_HYSTERESIS_VAL               3           	    //方向回滞，重复确认次数以减少误触发


#endif
