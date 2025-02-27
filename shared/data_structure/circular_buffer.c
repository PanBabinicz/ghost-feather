#include "data_structure/circular_buffer.h"

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
///
/// \brief The circular buffer structure.
///
typedef struct
{
    uint8_t rear;
    uint8_t front;
    uint8_t overflow;
    uint8_t data[CIRCULAR_BUFFER_LENGTH];
} circular_buffer_t;

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \breif The circular buffer structure array.
///
static circular_buffer_t circular_buffer_array[CIRCULAR_BUFFER_INSTANCE_TOTAL];

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \breif Gets the circular buffer structure from given instance.
///
/// \param[in] instance        The instance of the circular buffer data structure.
/// \param[in] circular_buffer The address of the circular buffer pointer which will point to the
///                            address of the one instance from the static array.
///
/// \return circular_buffer_result_t                Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS          On success.
/// \retval CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE On invalid instace.
/// \retval CIRCULAR_BUFFER_RESULT_NULL_POINTER     On null pointer.
///
static circular_buffer_result_t circular_buffer_get(circular_buffer_instance_t instance,
                                                    circular_buffer_t **circular_buffer);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static circular_buffer_result_t circular_buffer_get(circular_buffer_instance_t instance,
                                                    circular_buffer_t **circular_buffer)
{
    /* Check if you don't dereference NULL pointer. Undefined behavior. */
    if (circular_buffer == NULL)
    {
        return CIRCULAR_BUFFER_RESULT_NULL_POINTER;
    }

    if ((instance < CIRCULAR_BUFFER_INSTANCE_0) || (instance >= CIRCULAR_BUFFER_INSTANCE_TOTAL))
    {
        return CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE;
    }

    *circular_buffer = &circular_buffer_array[instance];

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
circular_buffer_result_t circular_buffer_get_data(const circular_buffer_instance_t instance,
                                                  uint8_t *const buffer, const uint32_t buffer_size)
{
    if (buffer == NULL)
    {
        return CIRCULAR_BUFFER_RESULT_NULL_POINTER;
    }

    circular_buffer_t *circular_buffer;

    if (circular_buffer_get(instance, &circular_buffer) != CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        return CIRCULAR_BUFFER_RESULT_ERROR;
    }

    if (buffer_size != sizeof(circular_buffer->data))
    {
        return CIRCULAR_BUFFER_RESULT_ERROR;
    }

    memcpy(&buffer[0], &circular_buffer->data[0], buffer_size);

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}

circular_buffer_result_t circular_buffer_set_data(const circular_buffer_instance_t instance,
                                                  const uint8_t *const buffer, const uint32_t buffer_size)
{
    if (buffer == NULL)
    {
        return CIRCULAR_BUFFER_RESULT_NULL_POINTER;
    }

    circular_buffer_t *circular_buffer;

    if (circular_buffer_get(instance, &circular_buffer) != CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        return CIRCULAR_BUFFER_RESULT_ERROR;
    }

    if (buffer_size != sizeof(circular_buffer->data))
    {
        return CIRCULAR_BUFFER_RESULT_ERROR;
    }

    memcpy(&circular_buffer->data[0], &buffer[0], buffer_size);

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}

circular_buffer_result_t circular_buffer_set_state(const circular_buffer_instance_t instance, const uint8_t rear,
                                                   const uint8_t front, const uint8_t overflow)
{
    circular_buffer_t *circular_buffer;

    if (circular_buffer_get(instance, &circular_buffer) != CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        return CIRCULAR_BUFFER_RESULT_ERROR;
    }

    circular_buffer->rear     = rear;
    circular_buffer->front    = front;
    circular_buffer->overflow = overflow;

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}

circular_buffer_result_t circular_buffer_clear(circular_buffer_instance_t instance)
{
    circular_buffer_t *circular_buffer;

    if (circular_buffer_get(instance, &circular_buffer) != CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        return CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE;
    }

    memset(circular_buffer, 0, sizeof(*circular_buffer));

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}

circular_buffer_result_t circular_buffer_clear_all(void)
{
    for (uint32_t i = CIRCULAR_BUFFER_INSTANCE_0; i < CIRCULAR_BUFFER_INSTANCE_TOTAL; i++)
    {
        if (circular_buffer_clear(i) != CIRCULAR_BUFFER_RESULT_SUCCESS)
        {
            return CIRCULAR_BUFFER_RESULT_ERROR;
        }
    }

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}

circular_buffer_result_t circular_buffer_push(circular_buffer_instance_t instance, uint8_t element)
{
    circular_buffer_t *circular_buffer;

    if (circular_buffer_get(instance, &circular_buffer) != CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        return CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE;
    }

    circular_buffer->data[circular_buffer->front] = element;

    if (((circular_buffer->front + 1) % CIRCULAR_BUFFER_LENGTH) == circular_buffer->rear)
    {
        circular_buffer->rear     = (circular_buffer->rear + 1) % CIRCULAR_BUFFER_LENGTH;
        circular_buffer->overflow = 1;
    }

    circular_buffer->front = (circular_buffer->front + 1) % CIRCULAR_BUFFER_LENGTH;

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}

circular_buffer_result_t circular_buffer_pop(circular_buffer_instance_t instance, uint8_t *element)
{
    circular_buffer_t *circular_buffer;

    if (element == NULL)
    {
        return CIRCULAR_BUFFER_RESULT_NULL_POINTER;
    }

    if (circular_buffer_get(instance, &circular_buffer) != CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        return CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE;
    }

    if ((circular_buffer->rear == circular_buffer->front) && (circular_buffer->overflow == 0))
    {
        return CIRCULAR_BUFFER_RESULT_EMPTY;
    }
    else if ((circular_buffer->rear == circular_buffer->front) && (circular_buffer->overflow == 1))
    {
        circular_buffer->overflow = 0;
    }

    *element              = circular_buffer->data[circular_buffer->rear];
    circular_buffer->rear = (circular_buffer->rear + 1) % CIRCULAR_BUFFER_LENGTH;

    return CIRCULAR_BUFFER_RESULT_SUCCESS;
}
