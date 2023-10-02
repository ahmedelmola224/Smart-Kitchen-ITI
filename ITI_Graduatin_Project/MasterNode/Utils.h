


#ifndef UTILS_H_
#define UTILS_H_

#define  SET_BIT(REG,BIT)      (REG=(1<<BIT)|(REG))
#define  CLR_BIT(REG,BIT)	   (REG=(~(1<<BIT))&REG)
#define  READ_BIT(REG,BIT)			 ((REG>>BIT)&1)
#define  TOG_BIT(REG,BIT)       (REG=REG^(1<<BIT))
#define  WRBIT(REG,BIT,VALUE)   (REG=((~(1<<BIT))&REG)|(VALUE<<BIT))


#endif 