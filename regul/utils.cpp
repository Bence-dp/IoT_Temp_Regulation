#include <math.h>
#include <Arduino.h>


float distanceKm(float lat1, float lon1, float lat2, float lon2) {
  const float R = 6371.0; // Rayon de la Terre en km

  float dLat = radians(lat2 - lat1);
  float dLon = radians(lon2 - lon1);

  lat1 = radians(lat1);
  lat2 = radians(lat2);

  float a = sin(dLat/2) * sin(dLat/2) +
             cos(lat1) * cos(lat2) *
             sin(dLon/2) * sin(dLon/2);

  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  return R * c;  // Distance en km
}