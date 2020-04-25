#define LIMIT 20

typedef struct {
  int arr[LIMIT];
  int pos;
  int sign;
}high_prec_t;

int scanHighPrec(high_prec_t* h);
void printHighPrec(high_prec_t h);