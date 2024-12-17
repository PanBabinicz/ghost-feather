#include "dust.h"

#define DUST_CRC16_LUT_SIZE (256u)

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \breif Circular buffer data structure array.
///
static uint16_t dust_crc16_lut[DUST_CRC16_LUT_SIZE];

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \breif Serialize the packet.
///
/// \param[in] packet The dust packet.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_serialize(dust_packet_t *packet);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static dust_result_t dust_serialize(dust_packet_t *packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
dust_result_t dust_crc16_generate_lut(uint16_t polynomial)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}

dust_result_t dust_crc16_calculate(dust_packet_t *packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}

dust_result_t dust_transmit(dust_packet_t *packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}

dust_result_t dust_receive(dust_packet_t **packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}
