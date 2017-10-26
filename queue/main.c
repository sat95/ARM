/*---------------------------------------------
Simple C calling ASM Example
 ----------------------------------------------*/

#include "audio.h"
#include "FM4_slider_interface.h"

// Create (instantiate) GUI slider data structure
struct FM4_slider_struct FM4_GUI;

// Norm squared in C prototype
int16_t norm_sq_c(int16_t* v, int16_t n);
// ASM function prototypes
extern uint32_t simple_sqrt(uint32_t x);
extern int16_t norm_sq_asm(int16_t *x, int16_t n);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main(void){
	int16_t x = 0;
	int16_t v[5] = {1,2,3,6,7};
	uint32_t zInt = 99;
	uint32_t zInt_sq;
	char message[50];
	
	// Initialize the slider interface by setting the baud rate (460800 or 921600)
	// and initial float values for each of the 6 slider parameters
	init_slider_interface(&FM4_GUI,460800, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0);
	
	gpio_set_mode(TEST_PIN,Output);
	
	// uint16_t Square root experiment
	gpio_set(TEST_PIN, HIGH); //Pin P10
	zInt_sq = simple_sqrt(zInt);
	gpio_set(TEST_PIN, LOW); //Pin P10
	sprintf(message, "uint16_t SQRT of %d is %d\n", zInt, zInt_sq);
	write_uart0(message);
	
	// Norm squared experiment
	gpio_set(TEST_PIN, HIGH); //Pin P10
	x = norm_sq_c (v, 5);	// call c function
	gpio_set(TEST_PIN, LOW); //Pin P10
	sprintf(message, "Norm squared C: The answer is %d\n", x);
	write_uart0(message);
	gpio_set(TEST_PIN, HIGH); //Pin P10
	x = norm_sq_asm (v, 5);	// call assembly function
	gpio_set(TEST_PIN, LOW); //Pin P10
	sprintf(message, "Norm squared ASM: The answer is %d\n", x);
	write_uart0(message);
	
  while(1)
	{
		// Update slider parameters
		//update_slider_parameters(&FM4_GUI);
	}
}

int16_t norm_sq_c(int16_t* v, int16_t n)
{
	int16_t i;
	int16_t out = 0;
	for(i=0; i<n; i++)
	{
		out += v[i]*v[i];		
	}	
	return out;
}
