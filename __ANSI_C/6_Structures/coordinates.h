// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com


typedef struct Point{\
						int32_t x;\
					 	int32_t y;\
					} point;

typedef struct Rectangle{\
						point p1;\
						point p2;\
						point p3;\
						point p4;\
						} rectangle;

// Prototypes
void init_rectangle();
void area_of_rectangle(rectangle);
