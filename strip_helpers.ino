void setupPlatform1LEDs()
{
    int index = 0;
    int offset = 0;
    int segment_end = NUM_PLATFORM_1_LEDS * 3;
    for (int i = offset; i < segment_end; i++)
    {
        platform_1_leds[index] = i;
        index++;
    }
}

void setupPlatform2LEDS()
{
    int index = 0;
    int offset = NUM_PLATFORM_1_LEDS * 3;
    int segment_end = offset + (NUM_PLATFORM_2_LEDS * 3);
    for (int i = offset; i < segment_end; i++)
    {
        platform_2_leds[index] = i;
        index++;
    }
}

void setupPlatform3LEDS()
{
    int index = 0;
    int offset = (NUM_PLATFORM_1_LEDS * 3) + (NUM_PLATFORM_2_LEDS * 3);
    int segment_end = offset + (NUM_PLATFORM_3_LEDS * 3);
    for (int i = offset; i < segment_end; i++)
    {
        platform_3_leds[index] = i;
        index++;
    }
}

void setupPlatform4LEDS()
{
    int index = 0;
    int offset = NUM_LOWER_LEDS + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
    int segment_end = offset + (NUM_PLATFORM_4_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        platform_4_leds[index] = i;
        index++;
    }
    offset = NUM_LOWER_LEDS + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
    segment_end = offset + (NUM_PLATFORM_4_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        platform_4_leds[index] = i;
        index++;
    }
    offset = NUM_LOWER_LEDS + (NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) * 2;
    segment_end = offset + (NUM_PLATFORM_4_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        platform_4_leds[index] = i;
        index++;
    }
}

void setupSpotLEDS()
{
    int index = 0;
    int offset = NUM_LOWER_LEDS + (NUM_ANTENNA_LEDS);
    int segment_end = offset + (NUM_SPOT_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        spot_leds[index] = i;
        index++;
    }
    offset = NUM_LOWER_LEDS + (NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
    segment_end = offset + (NUM_SPOT_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        spot_leds[index] = i;
        index++;
    }
    offset = NUM_LOWER_LEDS + (NUM_ANTENNA_LEDS) + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) * 2;
    segment_end = offset + (NUM_SPOT_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        spot_leds[index] = i;
        index++;
    }
}

void setupAntennaLEDS()
{
    // Antenna
    int index = 0;
    int offset = NUM_LOWER_LEDS;
    int segment_end = offset + (NUM_ANTENNA_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        antenna_leds[index] = i;
        index++;
    }
    offset = NUM_LOWER_LEDS + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS);
    segment_end = offset + (NUM_ANTENNA_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        antenna_leds[index] = i;
        index++;
    }
    offset = NUM_LOWER_LEDS + (NUM_PLATFORM_4_LEDS + NUM_SPOT_LEDS + NUM_ANTENNA_LEDS) * 2;
    segment_end = offset + (NUM_ANTENNA_LEDS);
    for (int i = offset; i < segment_end; i++)
    {
        antenna_leds[index] = i;
        index++;
    }
}