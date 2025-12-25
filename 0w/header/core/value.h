#ifndef __STDBOOL_H
    #define __STDBOOL_H
#else
    #undef false
    #undef true
#endif

#ifndef Value_DEFINE
#define Value_DEFINE

#define HeaderFunction static inline __attribute((always_inline))
#define value_error_state(turnback, runcode) (!(turnback = (turnback = (runcode)) == 0 ? (0) : (turnback)))
#define value_error_valid(turnback, errorcode, runcode) (!(turnback = (runcode) == 0 ? (errorcode) : (0)))

enum {
    Value_Error_Human = -6, Value_Error_Died, Value_Error_Broken, Value_Error_Render, Value_Error_Memory, Value_Error_IO, Value_Error_Fine,
    false = 0, true
};

extern const void* const null;

extern const double pi_deg;
extern const double pi_rad;

#endif
