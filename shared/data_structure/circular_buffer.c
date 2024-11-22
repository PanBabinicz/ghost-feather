#include "data_structure/circular_buffer.h"

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
///
/// \brief
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
/// \breif Circular buffer data structure array.
///
static circular_buffer_t circular_buffer_array[CIRCULAR_BUFFER_INSTANCE_TOTAL];

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \breif Get the circular buffer data structure from given instance.
///
/// \param[in] instance        The instance of the circular buffer data structure.
/// \param[in] circular_buffer The address of the circular buffer pointer which will point to the
///                            address of the one instance from the static array.
///
/// \return circular_buffer_result_t                Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS          On success.
/// \retval CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE On invalid instace.
/// \retval CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE On null pointer.
///
static circular_buffer_result_t circular_buffer_get(circular_buffer_instance_t instance,
                                                    circular_buffer_t **circular_buffer);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static circular_buffer_result_t circular_buffer_get(circular_buffer_instance_t instance,
                                                    circular_buffer_t **circular_buffer)
{
    circular_buffer_result_t result = CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE;

    // Check if you don't dereference NULL pointer. Undefined behavior.
    if (circular_buffer == NULL)
    {
        result = CIRCULAR_BUFFER_RESULT_NULL_POINTER;
    }
    else if ((instance >= CIRCULAR_BUFFER_INSTANCE_0) && (instance < CIRCULAR_BUFFER_INSTANCE_TOTAL))
    {
        *circular_buffer = &circular_buffer_array[instance];
        result           = CIRCULAR_BUFFER_RESULT_SUCCESS;
    }

    return result;
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
circular_buffer_result_t circular_buffer_clear(circular_buffer_instance_t instance)
{
    circular_buffer_result_t result = CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE;
    circular_buffer_t *circular_buffer;

    if (circular_buffer_get(instance, &circular_buffer) == CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        memset(circular_buffer, 0, sizeof(*circular_buffer));
        result = CIRCULAR_BUFFER_RESULT_SUCCESS;
    }

    return result;
}

circular_buffer_result_t circular_buffer_clear_all(void)
{
    circular_buffer_result_t result = CIRCULAR_BUFFER_RESULT_SUCCESS;

    for (size_t instance = CIRCULAR_BUFFER_INSTANCE_0; instance < CIRCULAR_BUFFER_INSTANCE_TOTAL;
         instance++)
    {
        if (circular_buffer_clear(instance) != CIRCULAR_BUFFER_RESULT_SUCCESS)
        {
            result = CIRCULAR_BUFFER_RESULT_ERROR;
            break;
        }
    }

    return result;
}

circular_buffer_result_t circular_buffer_push(circular_buffer_instance_t instance, uint8_t element)
{
    circular_buffer_result_t result = CIRCULAR_BUFFER_RESULT_ERROR;
    circular_buffer_t *circular_buffer;

    if (circular_buffer_get(instance, &circular_buffer) == CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        circular_buffer->data[circular_buffer->front] = element;

        if (((circular_buffer->front + 1) % CIRCULAR_BUFFER_LENGTH) == circular_buffer->rear)
        {
            circular_buffer->rear     = (circular_buffer->rear + 1) % CIRCULAR_BUFFER_LENGTH;
            circular_buffer->overflow = 1;
        }

        circular_buffer->front = (circular_buffer->front + 1) % CIRCULAR_BUFFER_LENGTH;
        result                 = CIRCULAR_BUFFER_RESULT_SUCCESS;
    }

    return result;
}

circular_buffer_result_t circular_buffer_pop(circular_buffer_instance_t instance, uint8_t *element)
{
    circular_buffer_result_t result = CIRCULAR_BUFFER_RESULT_EMPTY;
    circular_buffer_t *circular_buffer;

    if (element == NULL)
    {
        result = CIRCULAR_BUFFER_RESULT_NULL_POINTER;
    }
    else if (circular_buffer_get(instance, &circular_buffer) == CIRCULAR_BUFFER_RESULT_SUCCESS)
    {
        if ((circular_buffer->rear < circular_buffer->front) ||
           ((circular_buffer->rear > circular_buffer->front) && (circular_buffer->overflow == 1)))
        {
            *element = circular_buffer->data[circular_buffer->rear];
            circular_buffer->rear = (circular_buffer->rear + 1) % CIRCULAR_BUFFER_LENGTH;
            result = CIRCULAR_BUFFER_RESULT_SUCCESS;
        }
        else if ((circular_buffer->rear == circular_buffer->front) && (circular_buffer->overflow == 1))
        {
            *element                  = circular_buffer->data[circular_buffer->rear];
            circular_buffer->rear     = (circular_buffer->rear + 1) % CIRCULAR_BUFFER_LENGTH;
            circular_buffer->overflow = 0;
            result                    = CIRCULAR_BUFFER_RESULT_SUCCESS;
        }
    }

    return result;
}
