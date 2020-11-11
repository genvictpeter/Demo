/****************************************************************************
 	@Module       
 	@Filename      SysCtrl.c
 	@Project       BQApp
----------------------------------------------------------------------------
 	@Controller    TI 28034

 	@Compiler      V5.211

 	@Codegenerator CCS 3.3

 	@Description   

----------------------------------------------------------------------------
	 @Date          12/19/2014

******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****

****************************************************************************/
#include "DSP2803x_Device.h"			// Peripheral address definitions
#define  GET_TBPRD(x) 30000/x

struct CPUTIMER_VARS CpuTimer0;

#define Device_cal (void (*)(void))0x3D7C80    // Memory locations: Calibration Data, see 28023 Memory Map

void DisableDog(void);

/**********************************************************************
* Function: InitSysCtrl()
* Description: Initializes the F2802x CPU
**********************************************************************/
void InitSysCtrl(void)
{
	// Disable the watchdog
	DisableDog();

    // *IMPORTANT*
    // The Device_cal function, which copies the ADC & oscillator calibration values
    // from TI reserved OTP into the appropriate trim registers, occurs automatically
    // in the Boot ROM. If the boot ROM code is bypassed during the debug process, the
    // following function MUST be called for the ADC and oscillators to function according
    // to specification. The clocks to the ADC MUST be enabled before calling this
    // function.
    // See the device data manual and/or the ADC Reference
    // Manual for more information.

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; // Enable ADC peripheral clock
	(*Device_cal)();
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0; // Return ADC clock to original state
	EDIS;

	//-------------------------------------------------------------------------------------------------------
	EALLOW;

	//-------------------------------------
	//--- Memory Protection Configuration
	DevEmuRegs.DEVICECNF.bit.ENPROT = 1;	// Enable write/read protection

	//-------------------------------------
	// Configure the clock sources
	SysCtrlRegs.CLKCTL.bit.OSCCLKSRCSEL = 1;   // If user wishes to use Oscillator 2 or External Oscillator to clock the CPU, 
											   // they should configure this bit first
	SysCtrlRegs.CLKCTL.all = 0x2405;	// Configure the clock control register  

	// 0x2505  -->	select ext osc
	// bit 15        0:      NMIRESETSEL, NMI reset select for missing clock detect, 0=direct reset, 1=NMI WD causes reset
	// bit 14        0:      XTALOSCOFF, Crystal oscillator off, 0=on, 1=off
	// bit 13        1:      XCLKINOFF, XCLKIN input off, 0=on, 1=off
	// bit 12        0:      WDHALTI, WD halt ignore, 0=WD turned off by HALT, 1=WD ignores HALT
	// bit 11        0:      INTOSC2HALTI, OSC2 halt ignore, 0=OSC2 turned off by HALT, 1=OSC2 ignores HALT
	// bit 10        1:      INTOSC2OFF, OSC2 off, 0=on, 1=off
	// bit 9         0:      INTOSC1HALTI, OSC1 halt ignore, 0=OSC1 turned off by HALT, 1=OSC1 ignores HALT
	// bit 8         0:      INTOSC1OFF, OSC1 off, 0=on, 1=off
	// bit 7-5       000:    TMR2CLKPRESCALE, Timer2 prescale, 000=/1
	// bit 4-3       00:     TMR2CLKSCRSEL, Timer2 source, 00=SYSCLKOUT, 01=ext. OSC, 10=OSC1, 11=OSC2
	// bit 2         1:      WDCLKSRCSEL, WD source, 0=OSC1, 1=ext. OSC or OSC2
	// bit 1         0:      OSCCLKSRC2SEL, clock src2 select, 0=ext OSC, 1=OSC2
	// bit 0         1:      OSCCLKSRCSEL, clock src1 select, 0=OSC1, 1=ext. OSC or OSC2

	
	// 0x6400  --> 	select internal osc1
	// bit 15        0:      NMIRESETSEL, NMI reset select for missing clock detect, 0=direct reset, 1=NMI WD causes reset
	// bit 14        1:      XTALOSCOFF, Crystal oscillator off, 0=on, 1=off
	// bit 13        1:      XCLKINOFF, XCLKIN input off, 0=on, 1=off
	// bit 12        0:      WDHALTI, WD halt ignore, 0=WD turned off by HALT, 1=WD ignores HALT
	// bit 11        0:      INTOSC2HALTI, OSC2 halt ignore, 0=OSC2 turned off by HALT, 1=OSC2 ignores HALT
	// bit 10        1:      INTOSC2OFF, OSC2 off, 0=on, 1=off
	// bit 9         0:      INTOSC1HALTI, OSC1 halt ignore, 0=OSC1 turned off by HALT, 1=OSC1 ignores HALT
	// bit 8         0:      INTOSC1OFF, OSC1 off, 0=on, 1=off
	// bit 7-5       000:    TMR2CLKPRESCALE, Timer2 prescale, 000=/1
	// bit 4-3       00:     TMR2CLKSCRSEL, Timer2 source, 00=SYSCLKOUT, 01=ext. OSC, 10=OSC1, 11=OSC2
	// bit 2         0:      WDCLKSRCSEL, WD source, 0=OSC1, 1=ext. OSC or OSC2
	// bit 1         0:      OSCCLKSRC2SEL, clock src2 select, 0=ext OSC, 1=OSC2
	// bit 0         0:      OSCCLKSRCSEL, clock src1 select, 0=OSC1, 1=ext. OSC or OSC2

	//SysCtrlRegs.PLLSTS.bit.NORMRDYE = 1;

	SysCtrlRegs.XCLK.all = 0x0000;			// XCLKIN input off, no need to configure
	// bit 15-7    0's:      reserved
	// bit 6         1:      XCLKINSEL, XCLKIN source, 0=GPIO38, 1=GPIO19 (default) (Note: GPIO38 is JTAG TCK!)
	// bit 5-2     0's:      reserved
	// bit 1-0      00:      XCLKOUTDIV, XCLKOUT divide ratio, 00=SYSCLKOUT/4, 01=SYSCLKOUT/.2, 10=SYSCLKOUT, 11=off

	//-------------------------------------------------------------------------------------------------------
	//--- Configure the PLL
	// Make sure the PLL is not running in limp mode
	if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 1)            // PLL is not running in limp mode
	{													
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;				// DIVSEL must be 0 or 1 (/4 CLKIN mode) before changing PLLCR
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;				// Turn off missing clock detect before changing PLLCR
		
		SysCtrlRegs.PLLCR.bit.DIV = 0xC;				// PLL x 12/4 (because DIVSEL is /4), now SYSCLKOUT=10x12/4=30M
   
		// Wait for PLL to lock.
		// During this time the CPU will run at OSCCLK/4 until the PLL is stable.
		// Once the PLL is stable the CPU will automatically switch to the new PLL value.
		// Code is not required to sit and wait for the PLL to lock.  However, 
		// if the code does anything that is timing critical (e.g. something that
		// relies on the CPU clock frequency to be at speed), then it is best to wait
		// until PLL lock is complete.  The watchdog should be disabled before this loop
		// (e.g., as was done above), or fed within the loop.
		while (SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)		// Wait for PLLLOCKS bit to set
		{
			SysCtrlRegs.WDKEY = 0x0055;					// Service the watchdog while waiting
			SysCtrlRegs.WDKEY = 0x00AA;					// in case the user enabled it.
		}

		// After the PLL has locked, we are running in PLLx12/4 mode (since DIVSEL is /4).
		// We can now enable the missing clock detect circuitry, and also change DIVSEL
		// to /2.  In this example, I will wait a bit of time to let inrush currents settle,
		// and then change DIVSEL from /4 to /2.  This is only an example.  The amount of
		// time you need to wait depends on the power supply feeding the DSP (i.e., how much
		// voltage droop occurs due to the inrush currents, and how long it takes the
		// voltage regulators to recover).
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;				// Enable missing clock detect circuitry
		DelayUs(24);									// Wait 20 us (just an example).  Remember we're running
														// at half-speed here, so divide function argument by 2.
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 0x02;			// Change to /2 mode, now SYSCLKOUT=12x10/2=60M
	}
	else  // PLL is running in limp mode
	{													
		// User should replace the below with a call to an appropriate function,
		// for example shutdown the system (since something is very wrong!).
		asm(" ESTOP0");
	}
	
	//-------------------------------------------------------------------------------------------------------
	//--- Configure the clocks
	SysCtrlRegs.LOSPCP.all = 0x0002;			// Lo-speed periph clock prescaler, LOSPCLK=SYSCLKOUT/4
											//To 28035  SYSCLKOUT = 60MHz  LSPCLK = 15MHz

	SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;	// GPIO input module is clocked
	//SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 1;	// SYSCLKOUT to CPU Timer2 enabled
	//SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1;	// SYSCLKOUT to CPU Timer1 enabled
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1;	// SYSCLKOUT to CPU Timer0 enabled
	SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 1;		// SYSCLKOUT to COMP2 enabled
	SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 1;		// SYSCLKOUT to COMP1 enabled

	//SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;		// SYSCLKOUT to eCAP1 enabled

	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;		// SYSCLKOUT to ePWM1 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;		// SYSCLKOUT to ePWM2 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;		// SYSCLKOUT to ePWM3 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;		// SYSCLKOUT to ePWM4 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;		// SYSCLKOUT to ePWM4 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;		// SYSCLKOUT to ePWM4 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM7ENCLK = 1;		// SYSCLKOUT to ePWM4 enabled			


	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;		// LSPCLK to SCI-A enabled 
#ifdef DA_EN	
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;		// LSPCLK to SPI-A enabled
#endif	
	SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;		// SYSCLKOUT to I2C-A enabled
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;		// SYSCLKOUT to ADC enabled
	
	// TBCLKSYNC bit is handled separately in InitEPwm() since it affects ePWM synchronization.
	SysCtrlRegs.PCLKCR0.bit.HRPWMENCLK = 1;		// SYSCLKOUT to HRPWM enabled
	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;
	//--- Configure the low-power modes
	//SysCtrlRegs.LPMCR0.all = 0x00FC;		// LPMCR0 set to default value
	//InitCap();

	//--- Finish up
	EDIS;						// Disable EALLOW protected register access

} // end InitSysCtrl()


/**********************************************************************
* Function: InitGpio()
*
* Description: Initializes the shared GPIO pins on the F2802x
**********************************************************************/
void InitGpio(void)
{
	EALLOW;							// Enable EALLOW protected register access

	//-------------------------------------------------------------------------------------------------------
	//--- Group A pins
	GpioCtrlRegs.GPACTRL.all  = 0x00000000;		// QUALPRD = SYSCLKOUT for all group A GPIO
	GpioCtrlRegs.GPAQSEL1.all = 0x00000000;		// No qualification for all group A GPIO 0-15
	GpioCtrlRegs.GPAQSEL2.all = 0x00000000;		// No qualification for all group A GPIO 16-31
	GpioCtrlRegs.GPADIR.all   = 0x00000000;		// All group A GPIO are inputs
	
	//GpioCtrlRegs.GPAPUD.all   = 0x00000000;		// Pullups enabled GPIO0-31
	//GpioCtrlRegs.GPAPUD.all = 0xFFFFFFFF;   // Pullups disable GPIO0-31
	
	GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1;		// 0=GPIO         1=EPWM1A     2=rsvd       	3=rsvd  (used in Lab 3)
	GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1;		// 0=GPIO         1=EPWM1B     2=rsvd       	3=COMP1OUT
	GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1;		// 0=GPIO         1=EPWM2A     2=rsvd       	3=rsvd
	GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1;		// 0=GPIO         1=EPWM2B     2=rsvd       	3=COMP2OUT
	GpioCtrlRegs.GPAMUX1.bit.GPIO4  = 1;		// 0=GPIO         1=EPWM3A     2=rsvd       	3=rsvd
	GpioCtrlRegs.GPAMUX1.bit.GPIO5  = 1;		// 0=GPIO         1=EPWM3B     2=MFSRA      	3=ECAP1
	
	GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 0;		// 0=GPIO         1=EPWM4A     2=EPWMSYNCI  	3=EPWMSYNCO		RS485EN
	GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 1;		// 0=GPIO         1=EPWM4B     2=SCIRXDA    		3=rsvd		nRELAY
	
	GpioCtrlRegs.GPAMUX1.bit.GPIO8  = 1;		// 0=GPIO         1=EPWM5A     2=Reserved  	    3=ADCSOCAO (O)
	GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 1;		// 0=GPIO         1=EPWM5B     2=LINTXA (O)  	3=HRCAP1 (I)
	
	GpioCtrlRegs.GPAMUX1.bit.GPIO10  = 1;		// 0=GPIO         1=EPWM6A     2=Reserved 	    3=ADCSOCBO (O)
	GpioCtrlRegs.GPAMUX1.bit.GPIO11  = 0;		// 0=GPIO         1=EPWM6B     2=LINRXA (I) 	3=HRCAP2 (I)
	
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;		// 0=GPIO  1 = TZ1 (I)  2 = CITXDA (O)  3 = SPISIMOB (I/O)	//hardware OC INT

	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;        // 0=GPIO DRV  
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;        // 0=GPIO DRW  
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;        // 0=GPIO DRU  

	//16 - 19 & 24 SPI Interface 
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;		// 0=GPIO         1=SPISIMOA   2=rsvd       3=TZ2
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;		// 0=GPIO         1=SPISOMIA   2=rsvd       3=TZ3
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;		// 0=GPIO         1=SPICLKA    2=SCITXDA    3=XCLKOUT 
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;		// 0=GPIO/XCLKIN  1=SPISTEA    2=SCIRXDA    3=ECAP1

// AdPoint, test only		
	//GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;		// 0 =GPIO20  1 = EQEP1A (I)  2 = Reserved    3 = COMP1OUT (O)	
	//GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;		//0 = GPIO21  1= EQEP1B (I) 	2 = Reserved 3 =COMP2OUT (O)
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;		// AdPoint, test only	
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;		// AdPoint, test only	
	
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;		//0 = GPIO22  1 = EQEP1S (I/O) 2 = Reserved  3 = LINTXA (O)
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;		//0 = GPIO23  1 = EQEP1I (I/O) 2 = Reserved 3 = LINRXA (I)

	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;         // 0 = GPIO24  1 = ECAP1 (I/O)  2=Reserved  3=SPISIMOB (I/O)

	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0; 
	
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;		// 0=GPIO         1=SCIRXDA    2=SDAA       3=TZ2
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;		// 0=GPIO         1=SCITXDA    2=SCLA       3=TZ3
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;		// 0=GPIO         1=CANRXA (I)       2=rsvd       3=rsvd
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;		// 0=GPIO         1=CANTXA (O)       2=rsvd       3=rsvd

	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;		//0 = GPIO32  1= SDAA (I/OD)  2= EPWMSYNCI (I) 3=ADCSOCAO (O)
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;		//0 = GPIO33 1 = SCLA (I/OD) 2 = EPWMSYNCO (O) 3 =ADCSOCBO (O)
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;		//0 = GPIO34 1 = COMP2OUT (O)  2 = Reserved 3 = COMP3OUT (O)<BOOT1>

	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;        //GPIO--PT100_SEL
	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;		//0=GPIO41
	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;        //GPIO--MOT_NTC_SEL
	GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;        //0=GPIO44   key
	
	//-------------------------------------------------------------------------------------------------------
	//--- Group B pins
	GpioCtrlRegs.GPBCTRL.all  = 0x00000000;		// QUALPRD = SYSCLKOUT for all group B GPIO
	GpioCtrlRegs.GPBQSEL1.all = 0x00000000;		// No qualification for all group B GPIO 32-38
	GpioCtrlRegs.GPBDIR.all   = 0x00000000;		// All group B GPIO are inputs


	//-------------------------------------------------------------------------------------------------------
	// Analog I/O Mux pins
	GpioCtrlRegs.AIOMUX1.bit.AIO2  = 0;			// AIOx: 0=digital function, 2=analog function
	GpioCtrlRegs.AIOMUX1.bit.AIO4  = 2;			// AIOx: 0=digital function, 2=analog function  ATEXC
	GpioCtrlRegs.AIOMUX1.bit.AIO6  = 2;			// AIOx: 0=digital function, 2=analog function
	GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;			// AIOx: 0=digital function, 2=analog function
	GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;			// AIOx: 0=digital function, 2=analog function  15V 
	GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;			// AIOx: 0=digital function, 2=analog function  VDC
	//-------------------------------------------------------------------------------------------------------
	
	//--- External interrupt selection
	GpioIntRegs.GPIOXINT1SEL.all = 0x0C;		//GPIO12 is XINT source
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;        //Enable  XIntrupt
	XIntruptRegs.XINT1CR.bit.POLARITY = 0;		//00 Interrupt generated on a falling edge (high-to-low transition)
	//-------------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------------
	//--- Selected pin configurations
  	//GpioDataRegs.GPASET.all = 0xFFFFFFFF;   
  	
  	GpioDataRegs.GPASET.all = 0xFFFFFCFF;
  	GpioDataRegs.GPBSET.all = 0xFFFFFFFE;    // GPIO32 set low
	
  	GpioCtrlRegs.GPADIR.all   = 0xFFFFFFFF;   // all GPIOA(GPIO0 ~ GPIO31) direction set to output first

   	GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;		//FWD	 	
  	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;     // nFO
  	GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;		//IN 3  DRV  
  	GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;		//IN 4  DRW
  	GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;		//IN 5  DRU 
  	GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;		//SPI_SIMO
  	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;		//SPI_SOMI
  	GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;		//SPI_CLK
  	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;		//SPI_STE

// AdPoint, test only
  	//GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;		//QEP_A
  	//GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;		//QEP_B	
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;		// AdPoint, test only
  	GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;		// AdPoint, test only   450A or 600A   IN-0(450)  IN-1(600)
  	
  	GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;		//IN 9
  	GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;		//OC
  	
  	GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;		//SPI_CS
  	GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;		//IN 5
  	GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;		//IN 6
   	GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;		//IN 7
   	
  	GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;		//SCIRXDA

	GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;		//RX_CAN

	GpioCtrlRegs.GPAPUD.bit.GPIO7  = 0;       // Enable pull-up on GPIO7 (EPWM4B)
  	
  	GpioCtrlRegs.GPBDIR.all   = 0xFFFFFFFF;  // all GPIOB(GPIO32 ~ GPIO38) direction set to output first
  	
	//GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;		//ISP_BOOT1
	

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up for GPIO32 (SDAA)
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;	   // Enable pull-up for GPIO33 (SCLA)
	GpioCtrlRegs.GPBPUD.bit.GPIO44 = 0;	   // Enable pull-up for GPIO44 (NKEY)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // Asynch input GPIO32 (SDAA)
  	GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // Asynch input GPIO33 (SCLA)

/* Configure I2C pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be I2C functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   // Configure GPIO32 for SDAA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   // Configure GPIO33 for SCLA operation

	
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;
	
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;   //OUT PT100_SEL
	GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1;   //OUT NTC_SEL
	
	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;    //input  key

//Enable 485 Rsv
	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;

//Configure DA via SPI
#ifdef DA_EN
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;   // Disable pull-up on GPIO16

    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

/* Configure SPI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

	//GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;
	//GpioCtrlRegs.GPADIR.bit.GPIO19	 = 1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;	//Ouput /LOADDATA
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;// // Enable pull-up for GPIO33 
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; // Asynch input GPIO24
	
    EDIS;
#endif
	//-------------------------------------------------------------------------------------------------------
	//--- Finish up
	EDIS;								// Disable EALLOW protected register access

} // end InitGpio()


/**********************************************************************
* Description: Initializes the Enhanced PWM modules on the F2802x
**********************************************************************/
void InitEPwm(void)
{
	//---------------------------------------------------------------------
	//--- Must disable the clock to the ePWM modules if you       
	//--- want all ePMW modules synchronized.
	//---------------------------------------------------------------------
	asm(" EALLOW");						// Enable EALLOW protected register access
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	asm(" EDIS");						// Disable EALLOW protected register access
	//-------------------------------------------------------------------------------------------------------
    EALLOW;
    
    EPwm1Regs.TZSEL.bit.OSHT1 = 1;    // Enable TZ1 as a one-shot trip source for ePWM1 module
    EPwm2Regs.TZSEL.bit.OSHT1 = 1;    // Enable TZ1 as a one-shot trip source for ePWM2 module
    EPwm3Regs.TZSEL.bit.OSHT1 = 1;    // Enable TZ1 as a one-shot trip source for ePWM3 module
	
    // When a trip event occurs the following action is taken on 
    // output EPWMxB. Which trip-zone pins can cause an event is defined in the TZSEL register.
    EPwm1Regs.TZCTL.bit.TZB = 2;      // Force EPWM1B to a low state
    
    // When a trip event occurs the following action is taken on 
    // output EPWMxA. Which trip-zone pins can cause an event is defined in the TZSEL register.
    EPwm1Regs.TZCTL.bit.TZA = 2;     // Force EPWM1A to a low state
    
    // When a trip event occurs the following action is taken on 
    // output EPWMxB. Which trip-zone pins can cause an event is defined in the TZSEL register.
    EPwm2Regs.TZCTL.bit.TZB = 2;   // Force EPWM2B to a low state
    
    // When a trip event occurs the following action is taken on 
    // output EPWMxA. Which trip-zone pins can cause an event is defined in the TZSEL register.
    EPwm2Regs.TZCTL.bit.TZA = 2;   // Force EPWM2A to a low state    
    
	
    // When a trip event occurs the following action is taken on 
    // output EPWMxB. Which trip-zone pins can cause an event is defined in the TZSEL register.
    EPwm3Regs.TZCTL.bit.TZB = 2;   // Force EPWM3B to a low state
    
    // When a trip event occurs the following action is taken on 
    // output EPWMxA. Which trip-zone pins can cause an event is defined in the TZSEL register.
    EPwm3Regs.TZCTL.bit.TZA = 2;   // Force EPWM3A to a low state   
    
	
    EPwm1Regs.TZEINT.all = 0x0000;   // Disable TZ interrupt generation
    EPwm2Regs.TZEINT.all = 0x0000;   // Disable TZ interrupt generation
    EPwm3Regs.TZEINT.all = 0x0000;   // Disable TZ interrupt generation
	
    EPwm1Regs.TZFRC.bit.OST = 1;     // Forces a one-shot trip event and sets the TZFLG[OST] bit
    EPwm2Regs.TZFRC.bit.OST = 1;     // Forces a one-shot trip event and sets the TZFLG[OST] bit
    EPwm3Regs.TZFRC.bit.OST = 1;     // Forces a one-shot trip event and sets the TZFLG[OST] bit
    EPwm5Regs.TZFRC.bit.OST = 1;     // Forces a one-shot trip event and sets the TZFLG[OST] bit 
    //-------------------------------------------------------------------------------------------------------
    //EPWM1初始化:
    
//    EPwm1Regs.TBPRD = 3750;               // set the period of the time-base counter, up-down mode, SYSCLKOUT = 60M, 8k     
	EPwm1Regs.TBPRD = 7500;                 // beiqi4k

    //EPwm1Regs.TBCTR = 0x0000;               // set the current time-base counter value
    EPwm1Regs.TBCTR = 1200;                 // beiqi4k, (20us * 60M = 3240)
    
	EPwm1Regs.TBPHS.all = 0x0000;           // set time-base counter phase of the selected ePWM 
    
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 2;
    
    EPwm1Regs.TBCTL.bit.CTRMODE = 0x2;      // Up-down-count mode
    EPwm1Regs.TBCTL.bit.PHSEN = 0x0;        // Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
    EPwm1Regs.TBCTL.bit.PRDLD = 0x0;        // TBPRD is loaded from shadow register when TBCTR is equal to zero.
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 0x3;     // disable EPWMxSYNCO signal
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0x0;    // set HSPCLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT    
    EPwm1Regs.TBCTL.bit.CLKDIV = 0x0;       // set CLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT
	
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0x0;   // CMPA Register Operating Mode, Shadow mode,  vs: Immediate mode  
    
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0x2;   // Active Counter-Compare A (CMPA) Load From Shadow Select Mode.
                                              // This bit has no effect in immediate mode (CMPCTL[SHDWAMODE] = 1).
                                              // 00: Load on CTR = Zero: Time-base counter equal to zero (TBCTR = 0x0000)
                                              // 01: Load on CTR = PRD: Time-base counter equal to period (TBCTR = TBPRD)
                                              // 10: Load on either CTR = Zero or CTR = PRD
                                              // 10: Freeze (no loads possible)                            
    

    

    EPwm1Regs.CMPA.half.CMPA = 3750;      // beiqi4k
      
    EPwm1Regs.AQCTLA.bit.CAU = 0x2;         // Set: force EPWMxA output high 
    EPwm1Regs.AQCTLA.bit.CAD = 0x1;         // Clear: force EPWMxA output low
    
    EPwm1Regs.DBCTL.bit.IN_MODE = 0x0;      // EPWM1A In is the source for both falling-edge and rising-edge delay
    EPwm1Regs.DBCTL.bit.OUT_MODE = 0x3;     // Active Low Complementary 
    EPwm1Regs.DBCTL.bit.POLSEL = 2;         //Active high complementary (AHC). EPWMxB is inverted.
    
    //EPwm1Regs.DBFED = 192;   // (3.2us * 60M = 192)
    //EPwm1Regs.DBRED = 192;   // (3.2us * 60M = 192)
    EPwm1Regs.DBFED = 132;     // (2.2us * 60M = 132)
    EPwm1Regs.DBRED = 132;     // (2.2us * 60M = 132)    

    EPwm1Regs.ETCLR.all = 0x000F;           // Clear Register
    EPwm1Regs.ETSEL.bit.INTEN = 0;          // disable EPWM3_INT generation 
 //-------------------------------------------------------------------------------------------------------
    //EPWM2初始化:
    
	EPwm2Regs.TBPRD = 7500;                 // beiqi4k

    //EPwm2Regs.TBCTR = 0x0000;               // set the current time-base counter value
    EPwm2Regs.TBCTR = 1200;                 // beiqi4k, (20us * 60M = 3240)
        
    EPwm2Regs.TBPHS.all = 0x0000;           // set time-base counter phase of the selected ePWM 
    
    EPwm2Regs.TBCTL.bit.FREE_SOFT = 2;
    
    EPwm2Regs.TBCTL.bit.CTRMODE = 0x2;      // Up-down-count mode
    EPwm2Regs.TBCTL.bit.PHSEN = 0x0;        // Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
    EPwm2Regs.TBCTL.bit.PRDLD = 0x0;        // TBPRD is loaded from shadow register when TBCTR is equal to zero.
    EPwm2Regs.TBCTL.bit.SYNCOSEL = 0x3;     // disable EPWMxSYNCO signal
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0x0;    // set HSPCLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT    
    EPwm2Regs.TBCTL.bit.CLKDIV = 0x0;       // set CLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT
	
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0x0;   // CMPA Register Operating Mode, Shadow mode,  vs: Immediate mode  
    
    EPwm2Regs.CMPCTL.bit.LOADAMODE = 0x2;   // Active Counter-Compare A (CMPA) Load From Shadow Select Mode.
                                              // This bit has no effect in immediate mode (CMPCTL[SHDWAMODE] = 1).
                                              // 00: Load on CTR = Zero: Time-base counter equal to zero (TBCTR = 0x0000)
                                              // 01: Load on CTR = PRD: Time-base counter equal to period (TBCTR = TBPRD)
                                              // 10: Load on either CTR = Zero or CTR = PRD
                                              // 10: Freeze (no loads possible)                            
    
                         
    

    EPwm2Regs.CMPA.half.CMPA = 3750;      // beiqi4k
       
    EPwm2Regs.AQCTLA.bit.CAU = 0x2;         // Set: force EPWMxA output high 
    EPwm2Regs.AQCTLA.bit.CAD = 0x1;         // Clear: force EPWMxA output low
    
    EPwm2Regs.DBCTL.bit.IN_MODE = 0x0;      // EPWM2A In is the source for both falling-edge and rising-edge delay
    EPwm2Regs.DBCTL.bit.OUT_MODE = 0x3;     // Active Low Complementary 
    EPwm2Regs.DBCTL.bit.POLSEL = 2;         //Active high complementary (AHC). EPWMxB is inverted.
    
    //EPwm2Regs.DBFED = 192;   // (3.2us * 60M = 192)
    //EPwm2Regs.DBRED = 192;   // (3.2us * 60M = 192)
    EPwm2Regs.DBFED = 132;     // (2.2us * 60M = 132)
    EPwm2Regs.DBRED = 132;     // (2.2us * 60M = 132) 
    
    EPwm2Regs.ETCLR.all = 0x000F;           // Clear Register
    EPwm2Regs.ETSEL.bit.INTEN = 0;          // disable EPWM3_INT generation    
    
    //-------------------------------------------------------------------------------------------------------
    //EPwm3初始化:
    
	EPwm3Regs.TBPRD = 7500;                 // beiqi4k

    //EPwm3Regs.TBCTR = 0x0000;               // set the current time-base counter value
    EPwm3Regs.TBCTR = 1200;                 // beiqi4k, (20us * 60M = 3240)
    
    EPwm3Regs.TBPHS.all = 0x0000;           // set time-base counter phase of the selected ePWM 
    
    EPwm3Regs.TBCTL.bit.FREE_SOFT = 2;
    
    EPwm3Regs.TBCTL.bit.CTRMODE = 0x2;      // Up-down-count mode
    EPwm3Regs.TBCTL.bit.PHSEN = 0x0;        // Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
    EPwm3Regs.TBCTL.bit.PRDLD = 0x0;        // TBPRD is loaded from shadow register when TBCTR is equal to zero.
    EPwm3Regs.TBCTL.bit.SYNCOSEL = 0x3;     // disable EPWMxSYNCO signal
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0x0;    // set HSPCLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT    
    EPwm3Regs.TBCTL.bit.CLKDIV = 0x0;       // set CLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT
	
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0x0;   // CMPA Register Operating Mode, Shadow mode,  vs: Immediate mode  
    
    EPwm3Regs.CMPCTL.bit.LOADAMODE = 0x2;   // Active Counter-Compare A (CMPA) Load From Shadow Select Mode.
                                              // This bit has no effect in immediate mode (CMPCTL[SHDWAMODE] = 1).
                                              // 00: Load on CTR = Zero: Time-base counter equal to zero (TBCTR = 0x0000)
                                              // 01: Load on CTR = PRD: Time-base counter equal to period (TBCTR = TBPRD)
                                              // 10: Load on either CTR = Zero or CTR = PRD
                                              // 10: Freeze (no loads possible)                            
    
                             
    
  
    EPwm3Regs.CMPA.half.CMPA = 3750;      // beiqi4k
    
    EPwm3Regs.AQCTLA.bit.CAU = 0x2;         // Set: force EPWMxA output high 
    EPwm3Regs.AQCTLA.bit.CAD = 0x1;         // Clear: force EPWMxA output low
    
    EPwm3Regs.DBCTL.bit.IN_MODE = 0x0;      // EPWM2A In is the source for both falling-edge and rising-edge delay
    EPwm3Regs.DBCTL.bit.OUT_MODE = 0x3;     // Active Low Complementary 
    EPwm3Regs.DBCTL.bit.POLSEL = 2;         //Active high complementary (AHC). EPWMxB is inverted.
    
    //EPwm3Regs.DBFED = 192;   // (3.2us * 60M = 192)
    //EPwm3Regs.DBRED = 192;   // (3.2us * 60M = 192)
    EPwm3Regs.DBFED = 132;     // (2.2us * 60M = 132)
    EPwm3Regs.DBRED = 132;     // (2.2us * 60M = 132) 
    
    EPwm3Regs.ETCLR.all = 0x000F;           // Clear Register
    EPwm3Regs.ETSEL.bit.INTEN = 0;          // disable EPWM4_INT generation  
    //-------------------------------------------------------------------------------------------------------
   //EPWM5初始化: 用于 驱动电源
 
    //allen Gong:soft start of power,2016,3,1
 
    EPwm5Regs.TBCTR = 0x0;               // set the current time-base counter value
 
    EPwm5Regs.TBPRD = (GET_TBPRD(800)+1);       // set the period of the time-base counter, up-down mode, SYSCLKOUT = 60M, 430K
 
           //  TBPRD = 30000/f  
 
    EPwm5Regs.TBPRD = (GET_TBPRD(800)+1);       // set the period of the time-base counter, up-down mode, SYSCLKOUT = 60M, 430K
 
           //30000 = 30M hz  f(unit is kHz)
 
           // such as 430Khz 30000/430 = 70    
 
    EPwm5Regs.TBPHS.all = 0x0000;           // set time-base counter phase of the selected ePWM 
 
    EPwm5Regs.TBCTL.bit.FREE_SOFT = 2;
 
    
 
    EPwm5Regs.TBCTL.bit.CTRMODE = 0x2;      // Up-down-count mode
 
    EPwm5Regs.TBCTL.bit.PHSEN = 0x0;        // Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
 
    EPwm5Regs.TBCTL.bit.PRDLD = 0x0;        // TBPRD is loaded from shadow register when TBCTR is equal to zero.
 
    EPwm5Regs.TBCTL.bit.SYNCOSEL = 0x3;     // disable EPWMxSYNCO signal
 
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0x0;    // set HSPCLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT    
 
    EPwm5Regs.TBCTL.bit.CLKDIV = 0x0;       // set CLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT
 
 
 
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = 0x0;   // CMPA Register Operating Mode, Shadow mode,  vs: Immediate mode  
 
    EPwm5Regs.CMPCTL.bit.LOADAMODE = 0x0;   // Active Counter-Compare A (CMPA) load on CTR = Zero                             
 
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = 0x0;   // CMPA Register Operating Mode, Shadow mode,  vs: Immediate mode  
 
    EPwm5Regs.CMPCTL.bit.LOADBMODE = 0x0;   // Active Counter-Compare A (CMPA) load on CTR = Zero                             
 
    EPwm5Regs.CMPA.half.CMPA = (EPwm5Regs.TBPRD-1);
 
    EPwm5Regs.CMPA.half.CMPA = (EPwm5Regs.TBPRD-1);
 
    EPwm5Regs.CMPB=EPwm5Regs.TBPRD-EPwm5Regs.CMPA.half.CMPA;
 
    EPwm5Regs.CMPB=EPwm5Regs.TBPRD-EPwm5Regs.CMPA.half.CMPA;
 
    
 
    EPwm5Regs.AQCTLA.bit.CAU = 0x2;         // Set: force EPWMxA output high 
 
    EPwm5Regs.AQCTLA.bit.CAD = 0x1;         // Clear: force EPWMxA output low
 
//    EPwm5Regs.AQCTLA.bit.ZRO = 0x1;
 
    EPwm5Regs.AQCTLB.bit.CBU = 0x1;         // Set: force EPWMxB output low
 
    EPwm5Regs.AQCTLB.bit.CBD = 0x2;         // Clear: force EPWMxA output high
 
//    EPwm5Regs.AQCTLB.bit.ZRO = 0x1;
 
    
 
//      EPwm5Regs.DBCTL.bit.IN_MODE = 0x0;      // EPWM5A rising edge EPWM5B falling edge//In is the source for both falling-edge and rising-edge delay
 
    EPwm5Regs.DBCTL.bit.IN_MODE = 0x2;      // EPWM5A rising edge EPWM5B falling edge//In is the source for both falling-edge and rising-edge delay
 
    EPwm5Regs.DBCTL.bit.OUT_MODE = 0x0;     // Active high
 
    EPwm5Regs.DBCTL.bit.POLSEL = 0;         //Active high complementary (AHC). neither EPWMxB nor EPWMA is inverted.
 
    
 
    //EP5m3Regs.DBFED = 192;   // (3.2us * 60M = 192)
 
    //EP5m3Regs.DBRED = 192;   // (3.2us * 60M = 192)
 
    EPwm5Regs.DBFED = 0;     // (0.35us * 60M = 21)
 
    EPwm5Regs.DBRED = 0;     // (0.35us * 60M = 30)
 
    
 
    EPwm5Regs.ETCLR.all = 0x000F;           // Clear Register
 
    EPwm5Regs.ETSEL.bit.INTEN = 0;          // disable EPWM4_INT generation  
 
//allen Gong:soft start of power,2016,3,1

	//-------------------------------------------------------------------------------------------------------
	//EPWM4B初始化: 用于 RV_EXT 的幅值
	
	EPwm4Regs.TBCTR = 0x0000;				 // set the current time-base counter value
	EPwm4Regs.TBPRD = 3750; 				 // set the period of the time-base counter, up-down mode, SYSCLKOUT = 60M, 8k	   
	EPwm4Regs.TBPHS.all = 0x0000;			 // set time-base counter phase of the selected ePWM 
		
	EPwm4Regs.TBCTL.bit.FREE_SOFT = 2;
		
	EPwm4Regs.TBCTL.bit.CTRMODE = 0x2;		 // Up-down-count mode
	EPwm4Regs.TBCTL.bit.PHSEN = 0x0;		 // Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm4Regs.TBCTL.bit.PRDLD = 0x0;		 // TBPRD is loaded from shadow register when TBCTR is equal to zero.
	EPwm4Regs.TBCTL.bit.SYNCOSEL = 0x3; 	 // disable EPWMxSYNCO signal
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0x0;	 // set HSPCLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT    
	EPwm4Regs.TBCTL.bit.CLKDIV = 0x0;		 // set CLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT
		
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = 0; 	 // CMPB Register Operating Mode, Shadow mode,  vs: Immediate mode  
		
	EPwm4Regs.CMPCTL.bit.LOADBMODE = 2; 	 // Active Counter-Compare B (CMPB) Load From Shadow Select Mode. This bit has no 
											 // effect in immediate mode (CMPCTL[SHDWBMODE] = 1).	   												 // Load on either CTR = Zero or CTR = PRD							   
	EPwm4Regs.CMPB = 1;
		
	EPwm4Regs.AQCTLB.bit.CBU = 0x2; 		 // Set: force EPWMxB output high 
	EPwm4Regs.AQCTLB.bit.CBD = 0x1; 		 // Clear: force EPWMxB output low
		
	EPwm4Regs.DBCTL.bit.IN_MODE = 0x3;		 // EPWM1B In is the source for both falling-edge and rising-edge delay
	EPwm4Regs.DBCTL.bit.OUT_MODE = 0x3; 	 // Active Low Complementary 
	EPwm4Regs.DBCTL.bit.POLSEL = 1; 		 //Active high complementary (AHC). EPWMxB is inverted.
  
    //-------------------------------------------------------------------------------------------------------
    //EPWM6初始化: 用于 RV_EXT

    EPwm6Regs.TBCTR = 0x0000;                // set the current time-base counter value
    EPwm6Regs.TBPRD = 3750;                  // set the period of the time-base counter, up-down mode, SYSCLKOUT = 60M, 8k     
    EPwm6Regs.TBPHS.all = 0x0000;            // set time-base counter phase of the selected ePWM 
    
    EPwm6Regs.TBCTL.bit.FREE_SOFT = 2;
    
    EPwm6Regs.TBCTL.bit.CTRMODE = 0x2;       // Up-down-count mode
    EPwm6Regs.TBCTL.bit.PHSEN = 0x0;         // Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
    EPwm6Regs.TBCTL.bit.PRDLD = 0x0;         // TBPRD is loaded from shadow register when TBCTR is equal to zero.
    EPwm6Regs.TBCTL.bit.SYNCOSEL = 0x3;      // disable EPWMxSYNCO signal
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = 0x0;     // set HSPCLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT    
    EPwm6Regs.TBCTL.bit.CLKDIV = 0x0;        // set CLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT
	
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = 0;     // CMPA Register Operating Mode, Shadow mode,  vs: Immediate mode  
    
    EPwm6Regs.CMPCTL.bit.LOADAMODE = 2;      // Active Counter-Compare A (CMPA) Load From Shadow Select Mode. This bit has no 
                                             // effect in immediate mode (CMPCTL[SHDWAMODE] = 1).      
                                             // Load on either CTR = Zero or CTR = PRD                             
    EPwm6Regs.CMPA.half.CMPA = 1875;
    
    EPwm6Regs.AQCTLA.bit.CAU = 0x2;          // Set: force EPWMxA output high 
    EPwm6Regs.AQCTLA.bit.CAD = 0x1;          // Clear: force EPWMxA output low
    
    EPwm6Regs.DBCTL.bit.IN_MODE = 0x0;       // EPWM1A In is the source for both falling-edge and rising-edge delay
    EPwm6Regs.DBCTL.bit.OUT_MODE = 0x3;      // Active Low Complementary 
    EPwm6Regs.DBCTL.bit.POLSEL = 2;          //Active high complementary (AHC). EPWMxB is inverted.
    
    //-------------------------------------------------------------------------------------------------------
    //EPWM7初始化:   用于产生Tbase

    EPwm7Regs.TBCTR = 0x0000;               // set the current time-base counter value
    EPwm7Regs.TBPRD = 3750;                 // set the period of the time-base counter, up-down mode, SYSCLKOUT = 60M, 8k    
    EPwm7Regs.TBPHS.all = 0x0000;           // set time-base counter phase of the selected ePWM 
    
    EPwm7Regs.TBCTL.bit.FREE_SOFT = 2;
    
    EPwm7Regs.TBCTL.bit.CTRMODE = 0x2;      // Up-down-count mode
    EPwm7Regs.TBCTL.bit.PHSEN = 0x0;        // Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
    EPwm7Regs.TBCTL.bit.PRDLD = 0x0;        // TBPRD is loaded from shadow register when TBCTR is equal to zero.
    EPwm7Regs.TBCTL.bit.SYNCOSEL = 0x3;     // disable EPWMxSYNCO signal
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = 0x0;    // set HSPCLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT    
    EPwm7Regs.TBCTL.bit.CLKDIV = 0x0;       // set CLKDIV = 1, TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLKOUT
	
    EPwm7Regs.ETCLR.all = 0x000F;           // Clear Register
    EPwm7Regs.ETSEL.bit.INTEN = 1;          // Enable EPWM7_INT generation
    
    EPwm7Regs.ETSEL.bit.INTSEL = 3;         // EPWM7_INT Selection Options: 
                                            // Enable event time-base counter equal to zero or period (TBCTR = 0x0000 or TBCTR = TBPRD).
                                            // so, interrupt period is 62.5us
    
    EPwm7Regs.ETPS.bit.INTPRD = 1;          // Generate an interrupt on the first event INTCNT = 01 (first event)
    
    EPwm7Regs.ETSEL.bit.SOCASEL = 3;     // EPWM7SOCA Selection Options,These bits determine when a EPWMxSOCA pulse will be generated.
                                         // Enable event time-base counter equal to zero or period (TBCTR = 0x0000 or TBCTR = TBPRD).
    
    EPwm7Regs.ETPS.bit.SOCAPRD = 1;         // Generate the EPWMxSOCA pulse on the first event: ETPS[SOCACNT] = 1, 发生一次就触发一次采样                                        
    EPwm7Regs.ETSEL.bit.SOCAEN = 1;         // Enable the ADC Start of Conversion A (EPWMxSOCA) Pulse
    
	EPwm7Regs.CMPB = 0;    // 0 means EPWM7SOCA pulse will be generated when time-base counter equal to zero (TBCTR = 0x0000)  
    //-------------------------------------------------------------------------------------------------------
	
	
	EDIS;

	//---------------------------------------------------------------------
	//--- Enable the clocks to the ePWM module.                   
	//--- Note: this should be done after all ePWM modules are configured
	//--- to ensure synchronization between the ePWM modules.
	//---------------------------------------------------------------------
	asm(" EALLOW");							// Enable EALLOW protected register access
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;	// TBCLK to ePWM modules enabled
	asm(" EDIS");							// Disable EALLOW protected register access

}



/**********************************************************************
* Function: InitPieCtrl()
*
* Description: Initializes and enables the PIE interrupts on the F2802x
**********************************************************************/

extern const struct PIE_VECT_TABLE PieVectTableInit;

void InitPieCtrl(void)
{
	//-------------------------------------------------------------------------------------------------------
	//--- Disable interrupts
	asm(" SETC INTM, DBGM");			// Disable global interrupts

	//-------------------------------------------------------------------------------------------------------
	//--- Initialize the PIE_RAM
	PieCtrlRegs.PIECTRL.bit.ENPIE = 0;	// Disable the PIE
	asm(" EALLOW");						// Enable EALLOW protected register access
	memcpy(&PieVectTable, &PieVectTableInit, 256);
	asm(" EDIS");						// Disable EALLOW protected register access

	//-------------------------------------------------------------------------------------------------------
	//--- Disable all PIE interrupts
	PieCtrlRegs.PIEIER1.all =  0x0000;
	PieCtrlRegs.PIEIER2.all =  0x0000;
	PieCtrlRegs.PIEIER3.all =  0x0000;
	PieCtrlRegs.PIEIER4.all =  0x0000;
	PieCtrlRegs.PIEIER5.all =  0x0000;
	PieCtrlRegs.PIEIER6.all =  0x0000;
	PieCtrlRegs.PIEIER7.all =  0x0000;
	PieCtrlRegs.PIEIER8.all =  0x0000;
	PieCtrlRegs.PIEIER9.all =  0x0000;
	PieCtrlRegs.PIEIER10.all = 0x0000;
	PieCtrlRegs.PIEIER11.all = 0x0000;
	PieCtrlRegs.PIEIER12.all = 0x0000;

	//-------------------------------------------------------------------------------------------------------
	//--- Clear any potentially pending PIEIFR flags
	PieCtrlRegs.PIEIFR1.all  = 0x0000;
	PieCtrlRegs.PIEIFR2.all  = 0x0000;
	PieCtrlRegs.PIEIFR3.all  = 0x0000;	
	PieCtrlRegs.PIEIFR4.all  = 0x0000;
	PieCtrlRegs.PIEIFR5.all  = 0x0000;
	PieCtrlRegs.PIEIFR6.all  = 0x0000;
	PieCtrlRegs.PIEIFR7.all  = 0x0000;
	PieCtrlRegs.PIEIFR8.all  = 0x0000;
	PieCtrlRegs.PIEIFR9.all  = 0x0000;
	PieCtrlRegs.PIEIFR10.all = 0x0000;
	PieCtrlRegs.PIEIFR11.all = 0x0000;
	PieCtrlRegs.PIEIFR12.all = 0x0000;

	//-------------------------------------------------------------------------------------------------------
	//--- Acknowlege all PIE interrupt groups
	PieCtrlRegs.PIEACK.all = 0xFFFF;

	//-------------------------------------------------------------------------------------------------------
	//--- Enable the PIE
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;		// Enable the PIE

}


/**********************************************************************
* The PIE vector initialization table for the F2802x
**********************************************************************/
const struct PIE_VECT_TABLE PieVectTableInit = {

	//-------------------------------------------------------------------------------------------------------
	//--- Base vectors
    rsvd_ISR,                       // 0x000D00  reserved
    rsvd_ISR,                       // 0x000D02  reserved
    rsvd_ISR,                       // 0x000D04  reserved
    rsvd_ISR,                       // 0x000D06  reserved
    rsvd_ISR,                       // 0x000D08  reserved
    rsvd_ISR,                       // 0x000D0A  reserved
    rsvd_ISR,                       // 0x000D0C  reserved
    rsvd_ISR,                       // 0x000D0E  reserved
    rsvd_ISR,                       // 0x000D10  reserved
    rsvd_ISR,                       // 0x000D12  reserved
    rsvd_ISR,                       // 0x000D14  reserved
    rsvd_ISR,                       // 0x000D16  reserved
    rsvd_ISR,                       // 0x000D18  reserved
    TINT1_ISR,                      // 0x000D1A  TINT1 - CPU Timer1
    TINT2_ISR,                      // 0x000D1C  TINT2 - CPU Timer2
    DATALOG_ISR,                    // 0x000D1E  DATALOG - CPU data logging interrupt
    RTOSINT_ISR,                    // 0x000D20  RTOSINT - CPU RTOS interrupt
    EMUINT_ISR,                     // 0x000D22  EMUINT - CPU emulation interrupt
    NMI_ISR,                        // 0x000D24  NMI - XNMI interrupt
    ILLEGAL_ISR,                    // 0x000D26  ILLEGAL - illegal operation trap
    USER1_ISR,                      // 0x000D28  USER1 - software interrupt #1
    USER2_ISR,                      // 0x000D2A  USER2 - software interrupt #2
    USER3_ISR,                      // 0x000D2C  USER3 - software interrupt #3
    USER4_ISR,                      // 0x000D2E  USER4 - software interrupt #4
    USER5_ISR,                      // 0x000D30  USER5 - software interrupt #5
    USER6_ISR,                      // 0x000D32  USER6 - software interrupt #6
    USER7_ISR,                      // 0x000D34  USER7 - software interrupt #7
    USER8_ISR,                      // 0x000D36  USER8 - software interrupt #8
    USER9_ISR,                      // 0x000D38  USER9 - software interrupt #9
    USER10_ISR,                     // 0x000D3A  USER10 - software interrupt #10
    USER11_ISR,                     // 0x000D3C  USER11 - software interrupt #11
    USER12_ISR,                     // 0x000D3E  USER12 - software interrupt #12

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #1 re-map
    ADCINT1_ISR,                    // 0x000D40  ADC INT1
    ADCINT2_ISR,                    // 0x000D42  ADC INT2
    rsvd_ISR1,                       // 0x000D44  reserved
    XINT1_ISR,                      // 0x000D46  XINT1
    XINT2_ISR,                      // 0x000D48  XINT2
    ADCINT9_ISR,                    // 0x000D4A  ADC INT9
    TINT0_ISR,                      // 0x000D4C  TINT0 (CPU TIMER 0)
    WAKEINT_ISR,                    // 0x000D4E  WAKEINT (LPM/WD)

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #2 re-map
    EPWM1_TZINT_ISR,                // 0x000D50  EPWM1TZINT
    EPWM2_TZINT_ISR,                // 0x000D52  EPWM2TZINT
    EPWM3_TZINT_ISR,                // 0x000D54  EPWM3TZINT
    EPWM4_TZINT_ISR,                // 0x000D56  EPWM4TZINT
    rsvd_ISR,                       // 0x000D58  reserved
    rsvd_ISR,                       // 0x000D5A  reserved
    rsvd_ISR,                       // 0x000D5C  reserved
    rsvd_ISR,                       // 0x000D5E  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #3 re-map
    EPWM1_INT_ISR,                  // 0x000D60  EPWM1INT
    EPWM2_INT_ISR,                  // 0x000D62  EPWM2INT
    EPWM3_INT_ISR,                  // 0x000D64  EPWM3INT
    EPWM4_INT_ISR,                  // 0x000D66  EPWM4INT
    rsvd_ISR3,                       // 0x000D68  reserved
    rsvd_ISR3,                       // 0x000D6A  reserved
    rsvd_ISR3,                       // 0x000D6C  reserved
    rsvd_ISR3,                       // 0x000D6E  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #4 re-map
    ECAP1_INT_ISR,                  // 0x000D70  ECAP1INT
    rsvd_ISR,                       // 0x000D72  reserved
    rsvd_ISR,                       // 0x000D74  reserved
    rsvd_ISR,                       // 0x000D76  reserved
    rsvd_ISR,                       // 0x000D78  reserved
    rsvd_ISR,                       // 0x000D7A  reserved
    rsvd_ISR,                       // 0x000D7C  reserved
    rsvd_ISR,                       // 0x000D7E  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #5 re-map
    rsvd_ISR,                       // 0x000D80  reserved
    rsvd_ISR,                       // 0x000D82  reserved
    rsvd_ISR,                       // 0x000D84  reserved
    rsvd_ISR,                       // 0x000D86  reserved
    rsvd_ISR,                       // 0x000D88  reserved
    rsvd_ISR,                       // 0x000D8A  reserved
    rsvd_ISR,                       // 0x000D8C  reserved
    rsvd_ISR,                       // 0x000D8E  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #6 re-map
    SPIRXINTA_ISR,                  // 0x000D90  SPIRXINTA
    SPITXINTA_ISR,                  // 0x000D92  SPIRXINTA
    rsvd_ISR,                       // 0x000D94  reserved
    rsvd_ISR,                       // 0x000D96  reserved
    rsvd_ISR,                       // 0x000D98  reserved
    rsvd_ISR,                       // 0x000D9A  reserved
    rsvd_ISR,                       // 0x000D9C  reserved
    rsvd_ISR,                       // 0x000D9E  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #7 re-map
    rsvd_ISR,                       // 0x000DA0  reserved
    rsvd_ISR,                       // 0x000DA2  reserved
    rsvd_ISR,                       // 0x000DA4  reserved
    rsvd_ISR,                       // 0x000DA6  reserved
    rsvd_ISR,                       // 0x000DA8  reserved
    rsvd_ISR,                       // 0x000DAA  reserved
    rsvd_ISR,                       // 0x000DAC  reserved
    rsvd_ISR,                       // 0x000DAE  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #8 re-map
    I2CINT1A_ISR,                   // 0x000DB0  I2CINT1A (I2C-A)
    I2CINT2A_ISR,                   // 0x000DB2  I2CINT2A (I2C-A)
    rsvd_ISR,                       // 0x000DB4  reserved
    rsvd_ISR,                       // 0x000DB6  reserved
    rsvd_ISR,                       // 0x000DB8  reserved
    rsvd_ISR,                       // 0x000DBA  reserved
    rsvd_ISR,                       // 0x000DBC  reserved
    rsvd_ISR,                       // 0x000DBE  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #9 re-map
    SCIRXINTA_ISR,                  // 0x000DC0  SCIRXINTA (SCI-A)
    SCITXINTA_ISR,                  // 0x000DC2  SCITXINTA (SCI-A)
    rsvd_ISR,                       // 0x000DC4  reserved
    rsvd_ISR,                       // 0x000DC6  reserved
    rsvd_ISR,                       // 0x000DC8  reserved
    rsvd_ISR,                       // 0x000DCA  reserved
    rsvd_ISR,                       // 0x000DCC  reserved
    rsvd_ISR,                       // 0x000DCE  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #10 re-map
    rsvd_ISR,                       // 0x000DD0  reserved, If this is ADCINT1_ISR, then INT1.1 should be rsvd_ISR
    rsvd_ISR,                       // 0x000DD2  reserved, If this is ADCINT2_ISR, then INT1.2 should be rsvd_ISR
    ADCINT3_ISR,                    // 0x000DD4  ADC INT3
    ADCINT4_ISR,                    // 0x000DD6  ADC INT4
    ADCINT5_ISR,                    // 0x000DD8  ADC INT5
    ADCINT6_ISR,                    // 0x000DDA  ADC INT6
    ADCINT7_ISR,                    // 0x000DDC  ADC INT7
    ADCINT8_ISR,                    // 0x000DDE  ADC INT8

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #11 re-map
    rsvd_ISR,                       // 0x000DE0  reserved
    rsvd_ISR,                       // 0x000DE2  reserved
    rsvd_ISR,                       // 0x000DE4  reserved
    rsvd_ISR,                       // 0x000DE6  reserved
    rsvd_ISR,                       // 0x000DE8  reserved
    rsvd_ISR,                       // 0x000DEA  reserved
    rsvd_ISR,                       // 0x000DEC  reserved
    rsvd_ISR,                       // 0x000DEE  reserved

	//-------------------------------------------------------------------------------------------------------
	//--- Core interrupt #12 re-map
    XINT3_ISR,                      // 0x000DF0  XINT3
    rsvd_ISR,                       // 0x000DF2  reserved
    rsvd_ISR,                       // 0x000DF4  reserved
    rsvd_ISR,                       // 0x000DF6  reserved
    rsvd_ISR,                       // 0x000DF8  reserved
    rsvd_ISR,                       // 0x000DFA  reserved
    rsvd_ISR,                       // 0x000DFC  reserved
    rsvd_ISR,                       // 0x000DFE  reserved

}; 

//**********************************************************************
// This function disables the watchdog timer.
void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
	// bit 15-8      0's:    reserved
	// bit 7         1:      WDFLAG, write 1 to clear
	// bit 6         1:      WDDIS, 1=disable WD
	// bit 5-3       101:    WDCHK, WD check bits, always write as 101b
	// bit 2-0       000:    WDPS, WD prescale bits, 000: WDCLK=OSCCLK/512/1    
    EDIS;
}
//**********************************************************************
void EnableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR = 0x002B;//10000000/512/4/256=50ms
    EDIS;
} 
//**********************************************************************
void KickDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
} 


/**********************************************************************
* Function: InitFlash()
* Description: Initializes the F2802x flash timing registers.
* Notes:
*  1) This function MUST be executed out of RAM.  Executing it out of
*     OTP/FLASH will produce unpredictable results.
*  2) The flash registers are code security module protected.  Therefore,
*     you must either run this function from secure RAM (L0),
*     or you must first unlock the CSM.  Note that unlocking the CSM as
*     part of the program flow can compromise the code security.
* 3) The latest datasheet for the particular device of interest should
*    be consulted to confirm the flash timing specifications.
**********************************************************************/
#pragma CODE_SECTION(InitFlash, "ramfuncs")
void InitFlash(void)
{
	asm(" EALLOW");									// Enable EALLOW protected register access
	FlashRegs.FPWR.bit.PWR = 3;						// Pump and bank set to active mode
	FlashRegs.FSTATUS.bit.V3STAT = 1;				// Clear the 3VSTAT bit
	FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;	// Sleep to standby transition cycles
	FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;	// Standby to active transition cycles
	FlashRegs.FBANKWAIT.bit.RANDWAIT = 2;			// Random access waitstates
	FlashRegs.FBANKWAIT.bit.PAGEWAIT = 2;			// Paged access waitstates
	FlashRegs.FOTPWAIT.bit.OTPWAIT = 2;				// OTP waitstates
	FlashRegs.FOPT.bit.ENPIPE = 1;					// Enable the flash pipeline
	asm(" EDIS");									// Disable EALLOW protected register access

	// Force a complete pipeline flush to ensure that the write to the last register
	// configured occurs before returning.  Safest thing is to wait 8 full cycles.

    asm(" RPT #6 || NOP");

}


/**********************************************************************
Description: Initializes the ADC on the F2802x
**********************************************************************/
/*
	注: 根据TI文档 Piccolo MCU Silicon Errata (sprz292j).pdf, ADC有以下风险:
	
	1.  第一次采样的结果可能不正确，要舍弃。
		When the ADC conversions are initiated by any source of trigger in either sequential or
		simultaneous sampling mode, the first sample may not be the correct conversion result.
		For sequential mode, discard the first sample at the beginning of every series of
		conversions. For instance, if the application calls for a given series of conversions,
		SOC0→SOC1→SOC2, to initiate periodically, then set up the series instead as
		SOC0→SOC1→SOC2→SOC3 and only use the last three conversions, ADCRESULT1,
		ADCRESULT2, ADCRESULT3, thereby discarding ADCRESULT0.
		For simultaneous sample mode, discard the first sample of both the A and B channels at
		the beginning of every series of conversions.	
	
	2.  ACQPS 不要设为6或者7。
		The on-chip ADC takes 13 ADC clock cycles to complete a conversion after the
		sampling phase has ended. The result is then presented to the CPU on the 14th cycle
		post-sampling and latched on the 15th cycle into the ADC result registers. If the next
		conversion's sampling phase terminates on this 14th cycle, the results latched by the
		CPU into the result register are not assured to be valid across all operating conditions.
		Due to the nature of the sampling and conversion phases of the ADC, there are only
		two values of ACQPS (which controls the sampling window) that would result in the
		above condition occurring—ACQPS = 6 or 7. One solution is to avoid using these
		values in ACQPS.
*/
void InitAdc(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access

	//-------------------------------------------------------------------------------------------------------
	//--- Call the Device_cal() function located in reserved OTP.
	//    Device_cal is a macro defined in the file SysCtrl.c.  This
	//    macro simply defines Device_cal to be a function pointer to
	//    the correct address in the reserved OTP.  Note that the device cal function
	//    is automatically called by the bootloader.  A call to this function is
	//    included here just in case the bootloader is bypassed during development.
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	(*Device_cal)();
	//-------------------------------------------------------------------------------------------------------
	//--- Reset the ADC module
	// Note: The ADC is already reset after a DSP reset, but this example is just showing
	// good coding practice to reset the peripheral before configuring it as you never
	// know why the DSP has started the code over again from the beginning.  
	//AdcRegs.ADCCTL1.bit.RESET = 1;		// Reset the ADC
	
	// Must wait 2 ADCCLK periods for the reset to take effect.
	// Note that ADCCLK = SYSCLKOUT for F2802x/F2803x devices.
	asm(" NOP");
	asm(" NOP");
	
	//--- Power-up and configure the ADC
	AdcRegs.ADCCTL1.all = 0x00E0;		// Power-up reference and main ADC
	// bit 15        0:      RESET, ADC software reset, 0=no effect, 1=resets the ADC
	// bit 14        0:      ADCENABLE, ADC enable, 0=disabled, 1=enabled
	// bit 13        0:      ADCBSY, ADC busy, read-only
	// bit 12-8      0's:    ADCBSYCHN, ADC busy channel, read-only
	// bit 7         1:      ADCPWDN, ADC power down, 0=powered down, 1=powered up
	// bit 6         1:      ADCBGPWD, ADC bandgap power down, 0=powered down, 1=powered up 
	// bit 5         1:      ADCREFPWD, ADC reference power down, 0=powered down, 1=powered up 
	// bit 4         0:      reserved
	// bit 3         0:      ADCREFSEL, ADC reference select, 0=internal, 1=external
	// bit 2         0:      INTPULSEPOS, INT pulse generation, 0=start of conversion, 1=end of conversion
	// bit 1         0:      VREFLOCONV, VREFLO convert, 0=VREFLO not connected, 1=VREFLO connected to B5
	// bit 0         0:      Must write as 0.
	
	//-------------------------------------------------------------------------------------------------------
	//--- SOC configuration
	AdcRegs.ADCSAMPLEMODE.all = 0xF;	//SOC0 - 7  Simultaneous sample
	// bit 15:8 reserved
	// bit 7: SIMULEN14    0: Single sample mode set for SOC14 and SOC15,  1: Simultaneous sample for SOC14 and SOC15.
	// bit 6: SIMULEN12    0: Single sample mode set for SOC12 and SOC13,  1: Simultaneous sample for SOC12 and SOC13.
	// bit 5: SIMULEN10    0: Single sample mode set for SOC10 and SOC11,  1: Simultaneous sample for SOC10 and SOC11.
	// bit 4: SIMULEN8     0: Single sample mode set for SOC8  and SOC9,   1: Simultaneous sample for SOC8  and SOC9.	
	// bit 3: SIMULEN6     0: Single sample mode set for SOC6  and SOC7,   1: Simultaneous sample for SOC6  and SOC7.
	// bit 2: SIMULEN4     0: Single sample mode set for SOC4  and SOC5,   1: Simultaneous sample for SOC4  and SOC5.
	// bit 1: SIMULEN2     0: Single sample mode set for SOC2  and SOC3,   1: Simultaneous sample for SOC2  and SOC3.
	// bit 0: SIMULEN0     0: Single sample mode set for SOC0  and SOC1,   1: Simultaneous sample for SOC0  and SOC1.

	//-------------------------------------------------------------------------------------
	// Simultaneous sample ,No Use
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0x11;		 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0x3;			 // ADCINA3/ADCINB3 pair,  sin/cos
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles
	
	//-------------------------------------------------------------------------------------
	//SIN COS : Simultaneous sample 
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 0x11;		 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC2CTL.bit.CHSEL = 0x3;			 // ADCINA3/ADCINB3 pair,  sin/cos
	AdcRegs.ADCSOC2CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles

	//-------------------------------------------------------------------------------------
	//VDC2
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 0x11;		 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC4CTL.bit.CHSEL = 0x0;			 // Convert channel ADCINA0/ADCINB0 pair  (ADCINA0 ==VDC2)  ADCINB0 ==IGBT U
	AdcRegs.ADCSOC4CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles
	
	//-------------------------------------------------------------------------------------	
	// IU IV 
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL = 0x11;		 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC6CTL.bit.CHSEL = 0x1;			 // // ADCINA1/ADCINB1 pair Iu Iv 
	AdcRegs.ADCSOC6CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles	

	//-------------------------------------------------------------------------------------
	// NTCU KTY
/*	AdcRegs.ADCSOC7CTL.bit.TRIGSEL = 0x11;			 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC7CTL.bit.CHSEL = 5;			 // Convert channel ADCINA5  (KTY)
	AdcRegs.ADCSOC7CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles*/

	//（IW curr） -625A～+625A；
	AdcRegs.ADCSOC8CTL.bit.TRIGSEL = 0x11;		 // ADCTRIG17 – ePWM7, ADCSOCA   ATEXC
	AdcRegs.ADCSOC8CTL.bit.CHSEL = 0x0F;		 // Convert channel ADCINB7  （IW curr） -625A～+625A；	 
	AdcRegs.ADCSOC8CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles	

	//-------------------------------------------------------------------------------------
	//12V-DC
	AdcRegs.ADCSOC9CTL.bit.TRIGSEL = 0x11;			 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC9CTL.bit.CHSEL = 0x06;			 // Convert channel ADCINA6  (12VDC)
	AdcRegs.ADCSOC9CTL.bit.ACQPS = 9;			    // Acquisition window set to (9+1)=10 cycles	
  
	//15V-DC
	AdcRegs.ADCSOC14CTL.bit.TRIGSEL = 0x11;			 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC14CTL.bit.CHSEL = 0x0C;			 // Convert channel ADCINB4  (15VDC)
	AdcRegs.ADCSOC14CTL.bit.ACQPS = 9;			    // Acquisition window set to (9+1)=10 cycles

	//VDC1
	AdcRegs.ADCSOC15CTL.bit.TRIGSEL = 0x11;			 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC15CTL.bit.CHSEL   = 0x0E;			 // Convert channel ADCINB6  (VDC)
	AdcRegs.ADCSOC15CTL.bit.ACQPS   = 9;			 // Acquisition window set to (9+1)=10 cycles

	//-------------------------------------------------------------------------------------
	//NTCV NTCW
	AdcRegs.ADCSOC10CTL.bit.TRIGSEL = 0x11;			 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC10CTL.bit.CHSEL = 0x0D;			 // Convert channel ADCINB5  (IGBT V)
	AdcRegs.ADCSOC10CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles		

	AdcRegs.ADCSOC11CTL.bit.TRIGSEL = 0x11;			 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC11CTL.bit.CHSEL = 0x0A;			 // Convert channel ADCINB2  (IGBT W)
	AdcRegs.ADCSOC11CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles	

	
	//ATEXC
	AdcRegs.ADCSOC12CTL.bit.TRIGSEL = 0x11;		  // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC12CTL.bit.CHSEL = 0x04;		 // Convert channel ADCINA4  (AI1)
	AdcRegs.ADCSOC12CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles	
	
	//KTY
	AdcRegs.ADCSOC13CTL.bit.TRIGSEL = 0x11;			 // ADCTRIG17 – ePWM7, ADCSOCA
	AdcRegs.ADCSOC13CTL.bit.CHSEL = 0x05;			 // Convert channel ADCINA5  (KTY)
	AdcRegs.ADCSOC13CTL.bit.ACQPS = 9;			 // Acquisition window set to (9+1)=10 cycles	
	
//--------------------------------------------------------------------
// AdPoint, test only
// EOC中断，用以产生 ADCINT1 和 ADCINT2，通过在这两个中断里翻转特定IO的电平观察采样点是否正确
/*
AdcRegs.INTSEL1N2.bit.INT1SEL = 0;   // EOC0 is trigger for ADCINT1
AdcRegs.INTSEL1N2.bit.INT1E = 1;     // ADCINT1 is enabled
AdcRegs.INTSEL1N2.bit.INT1CONT = 1;  // ADCINT1 pulses are generated whenever an EOC pulse is generated irrespective if the flag bit is cleared or not.

AdcRegs.INTSEL1N2.bit.INT2SEL = 2;   // EOC2 is trigger for ADCINT2
AdcRegs.INTSEL1N2.bit.INT2E = 1;     // ADCINT2 is enabled
AdcRegs.INTSEL1N2.bit.INT2CONT = 1;  // ADCINT2 pulses are generated whenever an EOC pulse is generated irrespective if the flag bit is cleared or not.
*/
//-------------------------------------------------------------------------------------	
	
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;	// Enable the ADC	
	
	DelayUs(3000);		
	
	//-------------------------------------------------------------------------------------------------------
	//--- Finish up

	asm(" EDIS");						// Disable EALLOW protected register access

}



//---------------------------------------------------------------------------
//SCI初始化函数:
//---------------------------------------------------------------------------
void InitSci(void)
{	
	SciaRegs.SCIFFTX.all = 0xe040;   
	SciaRegs.SCIFFRX.all = 0x2050;      //receive level is 8
	SciaRegs.SCIFFCT.all = 0;	
	SciaRegs.SCICCR.all = 0x07;		    //one stop bit,no parity,8 data
    SciaRegs.SCICTL1.all = 0x03;		//sw reset=0,tx/rx enable
    SciaRegs.SCIHBAUD = 0x00;                        
    SciaRegs.SCILBAUD = 0x30;			//38400                        
	SciaRegs.SCICTL2.all = 0xc0;		//disable interrupt 
	SciaRegs.SCIPRI.all = 0; 	

	//SciaRegs.SCICCR.bit.LOOPBKENA = 1;
		
	SciaRegs.SCICTL1.bit.SWRESET = 1;   //sw reset = 1  
}

//G 1<=BRP<=65535: Baudrate = LSPCLK/((BRP+1)*8)

//--- end of file -----------------------------------------------------

/*
void InitSpi(void)
{    
	// Initialize SPI FIFO registers
    	//SpiaRegs.SPIFFTX.all=0xE040;
    	//SpiaRegs.SPIFFRX.all=0x2044;
    	SpiaRegs.SPIFFCT.all=0x0;	  

	SpiaRegs.SPICCR.all = 0;
	SpiaRegs.SPICCR.bit.SPISWRESET = 0;
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;	//Output on rising edge,when no data, SPICLK is low
	SpiaRegs.SPICCR.bit.SPILBK = 0;
	SpiaRegs.SPICCR.bit.SPICHAR = 0x0F;		//16bit
	
	SpiaRegs.SPICTL.all =0x000E;    		     // Enable master mode, normal phase,
                                                 				// enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR =0x0002;	    // 5M,    SpiaRegs.SPIBRR = (LSPCLK_HZ / SPIA_BAUD_RATE - 1);
    //SpiaRegs.SPIBRR = 0x0005;       // 2.5M									
      SpiaRegs.SPICCR.all =0x008F;		         // Relinquish SPI from Reset   
      SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission

}
*/
/*
int tmp1,tmp2,tmp3,tmp4;
//0 =< CHValue <= 4095
void DAXmit(Uint16 CH1Value,Uint16 CH2Value,Uint16 CH3Value,Uint16 CH4Value)
{
	CH1Value &= 0xFFF;
	CH2Value &= 0xFFF;
	CH3Value &= 0xFFF;
	CH4Value &= 0xFFF;
	
	// Transmit data
	LOADDAC = 1;		//Logic
	SpiaRegs.SPITXBUF= 0x0000 + CH1Value;
	while(SpiaRegs.SPISTS.bit.INT_FLAG  == 0) {;}
		tmp1 = SpiaRegs.SPIRXBUF;
	asm(" RPT #10 || NOP");			// > 15ns
	LOADDAC = 0;
	asm(" RPT #10 || NOP");			// > 45ns
	
	
	LOADDAC = 1;		//Logic
	SpiaRegs.SPITXBUF= 0x4000 + CH2Value;
	while(SpiaRegs.SPISTS.bit.INT_FLAG  == 0) {;}
		tmp2 = SpiaRegs.SPIRXBUF;
	asm(" RPT #10 || NOP");			// > 15ns
	LOADDAC = 0;
	asm(" RPT #10 || NOP");			// > 45ns
	
	
	LOADDAC = 1;		//Logic
	SpiaRegs.SPITXBUF= 0x8000 + CH3Value;
	while(SpiaRegs.SPISTS.bit.INT_FLAG  == 0) {;}
		tmp3 = SpiaRegs.SPIRXBUF;
	asm(" RPT #10 || NOP");			// > 15ns
	LOADDAC = 0;
	asm(" RPT #10 || NOP");			// > 45ns
	
	LOADDAC = 1;		//Logic
	SpiaRegs.SPITXBUF= 0xC000 + CH4Value;
	while(SpiaRegs.SPISTS.bit.INT_FLAG  == 0) {;}
		tmp4 = SpiaRegs.SPIRXBUF;
	asm(" RPT #10 || NOP");			// > 15ns
	LOADDAC = 0;
	//asm(" RPT #10 || NOP");		// > 45ns	 
}


void DAChnalOne(Uint16 CH1Value,Uint16 CH2Value)
{

	// Transmit data
	LOADDAC = 1;		//Logic
	SpiaRegs.SPITXBUF= 0x0000 + CH1Value;
	while(SpiaRegs.SPISTS.bit.INT_FLAG  == 0) {;}
		tmp1 = SpiaRegs.SPIRXBUF;
	asm(" RPT #10 || NOP");			// > 15ns
	LOADDAC = 0;
	asm(" RPT #10 || NOP");			// > 45ns
	
	
	LOADDAC = 1;		//Logic
	SpiaRegs.SPITXBUF= 0x4000 + CH2Value;
	while(SpiaRegs.SPISTS.bit.INT_FLAG  == 0) {;}
		tmp2 = SpiaRegs.SPIRXBUF;
	asm(" RPT #10 || NOP");			// > 15ns
	LOADDAC = 0;
	asm(" RPT #10 || NOP");			// > 45ns	
}
*/


/*
void InitCap()
{
   ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture interrupts
   ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP interrupt flags
   ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped
   
   // Configure peripheral registers
   ECap1Regs.ECCTL2.bit.CONT_ONESHT = 0;      // Continue
   ECap1Regs.ECCTL2.bit.STOP_WRAP = 0;        // Stop after Capture Event 1 in one-shot mode
											  //Wrap after Capture Event 1 in continuous mode.
   ECap1Regs.ECCTL1.bit.CAP1POL = 0;          // Rising edge
   ECap1Regs.ECCTL1.bit.CTRRST1 = 1;          // Difference operation         
   ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;         // Enable sync in
   ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;        // Pass through
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable capture units


   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;        // Start Counter
   ECap1Regs.ECCTL2.bit.REARM = 1;            // arm one-shot
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
}*/
