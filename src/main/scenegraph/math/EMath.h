#ifndef _EMATH_H__
#define _EMATH_H__

#include <math.h>
#include <limits.h>	// For INT_MAX / UINT_MAX#include <float.h>	// For FLT_MAX

namespace end2 {

class EMath {
public:
    static const float PI;
    static const float HALF_PI;

    static int atoiAndSeek(const char* _in, const char** _first_non_converted_pos_out) {
        if(!_in) {
            return 0;
        }

        bool negative = false;
        if('-' == *_in) {
            negative = true;
            ++_in;
        } else if('+' == *_in) {
            ++_in;
        }

        unsigned int unsignedValue = 0;
        while ((*_in >= '0') && (*_in <= '9')) {
            unsignedValue = (unsignedValue * 10) + (*_in - '0');
            ++_in;
            if(unsignedValue > (unsigned int) INT_MAX) {
                unsignedValue = (unsigned int) INT_MAX;
                break;
            }
        }

        if(_first_non_converted_pos_out)
            *_first_non_converted_pos_out = _in;

        if(negative) {
            return -((int) unsignedValue);
        } else {
            return (int) unsignedValue;
        }
    }

    static float atofAndSeek(const char * _in, const char** _first_non_converted_pos_out) {
        static const float fast_atof_table[16] = {
                0.f,
                0.1f,
                0.01f,
                0.001f,
                0.0001f,
                0.00001f,
                0.000001f,
                0.0000001f,
                0.00000001f,
                0.000000001f,
                0.0000000001f,
                0.00000000001f,
                0.000000000001f,
                0.0000000000001f,
                0.00000000000001f,
                0.000000000000001f };

        if(!_in) {
            return 0.f;
        }

        bool negative = false;
        if(*_in == '-') {
            negative = true;
            ++_in;
        }

        float value = strToFloatOnlyDigitCharacter_(_in, &_in);

        if(*_in == '.') {
            ++_in;

            const char * afterDecimal = _in;
            float decimal = strToFloatOnlyDigitCharacter_(_in, &afterDecimal);
            decimal *= fast_atof_table[afterDecimal - _in];

            value += decimal;

            _in = afterDecimal;
        }

        if('e' == *_in || 'E' == *_in) {
            ++_in;
            value *= (float) pow(10.0f, (float) atoiAndSeek(_in, &_in));
        }

        if(_first_non_converted_pos_out)
            *_first_non_converted_pos_out = _in;

        if(negative)
            return -value;

        return value;
    }

private:

    static float strToFloatOnlyDigitCharacter_(const char* _in, const char** _first_non_converted_pos_out = 0) {
        if(_first_non_converted_pos_out) {
            *_first_non_converted_pos_out = _in;
        }

        if(!_in) {
            return 0.f;
        }

        static const unsigned int MAX_SAFE_U32_VALUE = UINT_MAX / 10 - 10;
        float floatValue = 0.f;
        unsigned int intValue = 0;

        // Use integer arithmetic for as long as possible, for speed
        // and precision.
        while ((*_in >= '0') && (*_in <= '9')) {
            // If it looks like we're going to overflow, bail out
            // now and start using floating point.
            if(intValue >= MAX_SAFE_U32_VALUE) {
                break;
            }

            intValue = (intValue * 10) + (*_in - '0');
            ++_in;
        }

        floatValue = (float) intValue;

        // If there are any digits left to parse, then we need to use
        // floating point arithmetic from here.
        while ((*_in >= '0') && (*_in <= '9')) {
            floatValue = (floatValue * 10.f) + (float) (*_in - '0');
            ++_in;
            if(floatValue > FLT_MAX) { // Just give up.
                break;
            }
        }

        if(_first_non_converted_pos_out) {
            *_first_non_converted_pos_out = _in;
        }

        return floatValue;
    }
};

}

#endif	//_EMATH_H__
