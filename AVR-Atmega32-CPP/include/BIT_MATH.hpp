#define TOGGLE_BIT(number, n) ((number) ^= (1 << (n)))
#define CLEAR_BIT(number, n) ((number) &= ~(1 << (n)))
#define SET_BIT(number, n) ((number) |= (1 << (n)))
#define CHECK_BIT(number, n) ((number) & (1 << (n)))
