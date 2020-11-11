/****************************************************************************
 	@Module       
 	@Filename      F28035.cmd
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



MEMORY
{
PAGE 0:    /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */
   RAML0       : origin = 0x008100, length = 0x000100     /* on-chip RAM block L0 */
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
   FLASHINIT   : origin = 0x3E8000, length = 0x000020
   FLASH       : origin = 0x3E8100, length = 0x00AF00     /* on-chip FLASH Sector H - D*/      
   CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASH.  Program with all 0x0000 when CSM is in use. */
   BEGIN       : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASH.  Used for "boot to Flash" bootloader mode. */
   CSM_PWL_P0  : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASH.  CSM password locations in FLASHA */

   IQTABLES    : origin = 0x3FE000, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   : origin = 0x3FEB50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3   : origin = 0x3FEBDC, length = 0x0000AA	  /* IQ Math Tables in Boot ROM */

   ROM         : origin = 0x3FF27C, length = 0x000D44     /* Boot ROM */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */

PAGE 1 :   /* Data Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
           /* Registers remain on PAGE1                                                  */
   BOOT_RSVD   : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   
   L0_ASM0     : origin = 0x008000, length = 0x000040 
   L0_ASM1     : origin = 0x008040, length = 0x000040
   L0_ASM2     : origin = 0x008080, length = 0x000040
   L0_ASM3     : origin = 0x0080C0, length = 0x000040   
   
   RAML3       : origin = 0x008200, length = 0x001E00     /* on-chip RAM block L3 */
}

/* Allocate sections to memory blocks.
   Note:
         codestart user defined section in DSP28_CodeStartBranch.asm used to redirect code
                   execution when booting to flash
         ramfuncs  user defined section to store functions that will be copied from Flash into RAM
*/

SECTIONS
{

   /* Allocate program areas: */
   .cinit              : > FLASH,   	PAGE = 0
   .pinit              : > FLASH,     	PAGE = 0
   .text               : > FLASH,     	PAGE = 0
   .text_int           : > FLASH,     	PAGE = 0   
   
   codestart           : > BEGIN,     	PAGE = 0
   bootstart		   : > FLASHINIT,   PAGE = 0
   
   ramfuncs            : LOAD = FLASH,
                         RUN = RAML0,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         PAGE = 0

   csmpasswds          : > CSM_PWL_P0,  PAGE = 0
   csm_rsvd            : > CSM_RSVD,    PAGE = 0

   /* Allocate uninitalized data sections: */
   .stack              : > RAMM1,       PAGE = 1
   .ebss               : > RAML3,       PAGE = 1
   .esysmem            : > RAML3,       PAGE = 1
   .bss				   : > RAML3,		PAGE = 1	

   PAR_ASM0            : > L0_ASM0,     PAGE = 1
   PAR_ASM1            : > L0_ASM1,     PAGE = 1
   PAR_ASM2            : > L0_ASM2,     PAGE = 1
   PAR_ASM3            : > L0_ASM3,     PAGE = 1

   /* Initalized sections go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASH,      PAGE = 0
   .switch             : > FLASH,      PAGE = 0 
   ctrlconst		   : > FLASH,	   PAGE = 0 

   /* Allocate IQ math areas: */
   IQmath              : > FLASH,      PAGE = 0            /* Math Code */
   IQmathTables        : > IQTABLES,   PAGE = 0, TYPE = NOLOAD

  /* Uncomment the section below if calling the IQNexp() or IQexp()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)

   }
   */
    /* Uncomment the section below if calling the IQNasin() or IQasin()
       functions from the IQMath.lib library in order to utilize the
       relevant IQ Math table in Boot ROM (This saves space and Boot ROM
       is 1 wait-state). If this section is not uncommented, IQmathTables2
       will be loaded into other memory (SARAM, Flash, etc.) and will take
       up space, but 0 wait-state is possible.
    */
    /*
    IQmathTables3    : > IQTABLES3, PAGE = 0, TYPE = NOLOAD
    {

               IQmath.lib<IQNasinTable.obj> (IQmathTablesRam)

    }
    */

   /* .reset is a standard section used by the compiler.  It contains the */
   /* the address of the start of _c_int00 for C Code.   /*
   /* When using the boot ROM this section and the CPU vector */
   /* table is not needed.  Thus the default type is set here to  */
   /* DSECT  */
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS,     PAGE = 0, TYPE = DSECT

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

