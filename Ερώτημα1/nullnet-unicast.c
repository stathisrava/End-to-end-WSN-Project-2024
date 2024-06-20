/*
 * Copyright (c) 2017, RISE SICS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         NullNet unicast example
 * \author
*         Simon Duquennoy <simon.duquennoy@ri.se>
 *
 */
						/*
#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

#include <string.h>
#include <stdio.h> // For printf() //

// Log configuration //
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

// Configuration //
#define SEND_INTERVAL (8 * CLOCK_SECOND)
static linkaddr_t dest_addr =         {{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};

#if MAC_CONF_WITH_TSCH
#include "net/mac/tsch/tsch.h"
static linkaddr_t coordinator_addr =  {{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};
#endif // MAC_CONF_WITH_TSCH //

//---------------------------------------------------------------------------//
PROCESS(nullnet_example_process, "NullNet unicast example");
AUTOSTART_PROCESSES(&nullnet_example_process);

//---------------------------------------------------------------------------//
void input_callback(const void *data, uint16_t len,
  const linkaddr_t *src, const linkaddr_t *dest)
{
  if(len == sizeof(unsigned)) {
    unsigned count;
    memcpy(&count, data, sizeof(count));
    LOG_INFO("Received %u from ", count);
    LOG_INFO_LLADDR(src);
    LOG_INFO_("\n");
  }
}
//---------------------------------------------------------------------------//
PROCESS_THREAD(nullnet_example_process, ev, data)
{
  static struct etimer periodic_timer;
  static unsigned count = 0;

  PROCESS_BEGIN();

#if MAC_CONF_WITH_TSCH
  tsch_set_coordinator(linkaddr_cmp(&coordinator_addr, &linkaddr_node_addr));
#endif // MAC_CONF_WITH_TSCH //

  // Initialize NullNet //
  nullnet_buf = (uint8_t *)&count;
  nullnet_len = sizeof(count);
  nullnet_set_input_callback(input_callback);

  if(!linkaddr_cmp(&dest_addr, &linkaddr_node_addr)) {
    etimer_set(&periodic_timer, SEND_INTERVAL);
    while(1) {
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
      LOG_INFO("Sending %u to ", count);
      LOG_INFO_LLADDR(&dest_addr);
      LOG_INFO_("\n");

      NETSTACK_NETWORK.output(&dest_addr);
      count++;
      etimer_reset(&periodic_timer);
    }
  }

  PROCESS_END();
}
//---------------------------------------------------------------------------//
							*/
							
/*
 * Copyright (c) 2017, RISE SICS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         NullNet unicast example
 * \author
 *         Simon Duquennoy <simon.duquennoy@ri.se>
 *
 */

		/*

#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h> // For printf() //
#include "utils.h" 

// Log configuration //
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

// Configuration //
#define SEND_INTERVAL (20 * CLOCK_SECOND) // Adjusted to send every 20 seconds

// Set the destination address to the MAC address of the parent node
static linkaddr_t dest_addr = {{ 0x44, 0xc0, 0x60, 0x13, 0x00, 0x74, 0x12, 0x00 }};

#if MAC_CONF_WITH_TSCH
#include "net/mac/tsch/tsch.h"
static linkaddr_t coordinator_addr = {{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};
#endif // MAC_CONF_WITH_TSCH //

//---------------------------------------------------------------------------//
PROCESS(nullnet_example_process, "NullNet unicast example");
AUTOSTART_PROCESSES(&nullnet_example_process);

//---------------------------------------------------------------------------//
void input_callback(const void *data, uint16_t len,
                    const linkaddr_t *src, const linkaddr_t *dest)
{
  if (len == sizeof(unsigned)) {
    unsigned count;
    memcpy(&count, data, sizeof(count));
    LOG_INFO("Received %u from ", count);
    LOG_INFO_LLADDR(src);
    LOG_INFO_("\n");
  }
}
//---------------------------------------------------------------------------//
PROCESS_THREAD(nullnet_example_process, ev, data)
{
  static struct etimer periodic_timer;
  static unsigned count = 0;

  PROCESS_BEGIN();

#if MAC_CONF_WITH_TSCH
  tsch_set_coordinator(linkaddr_cmp(&coordinator_addr, &linkaddr_node_addr));
#endif // MAC_CONF_WITH_TSCH //

  // Initialize NullNet //
  nullnet_buf = (uint8_t *)&count;
  nullnet_len = sizeof(count);
  nullnet_set_input_callback(input_callback);

  // Check if the current node is not the destination node
  if (!linkaddr_cmp(&dest_addr, &linkaddr_node_addr)) {
    etimer_set(&periodic_timer, SEND_INTERVAL);
    while (1) {
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
      LOG_INFO("Sending %u to ", count);
      LOG_INFO_LLADDR(&dest_addr);
      LOG_INFO_("\n");

      // Send the data to the destination node
      NETSTACK_NETWORK.output(&dest_addr);
      count++;
      etimer_reset(&periodic_timer);
    }
  }

  PROCESS_END();
}
//---------------------------------------------------------------------------//

			*/
#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include "utils.h"
#include "arch/dev/sensor/sht11/sht11-sensor.h" // Include the sensor header
#include <string.h>
#include <stdio.h> // For printf()

// Log configuration
#include "sys/log.h"
#define LOG_MODULE "Leaf"
#define LOG_LEVEL LOG_LEVEL_INFO 

// Configuration
#define SEND_INTERVAL (20 * CLOCK_SECOND)
static linkaddr_t parent_addr = {{ 0x44, 0xc0, 0x60, 0x13, 0x00, 0x74, 0x12, 0x00 }}; // Replace with the actual MAC address of the parent node

#if MAC_CONF_WITH_TSCH
#include "net/mac/tsch/tsch.h"
static linkaddr_t coordinator_addr = {{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};
#endif // MAC_CONF_WITH_TSCH

PROCESS(leaf_node_process, "Leaf Node Process");
AUTOSTART_PROCESSES(&leaf_node_process);

static struct data_form sensor_data;

void input_callback(const void *data, uint16_t len, const linkaddr_t *src, const linkaddr_t *dest) {
  if(len == sizeof(struct data_form)) {
    struct data_form received_data;
    memcpy(&received_data, data, sizeof(received_data));
    char temp_str[20], hum_str[20];
    double2str(temp_str, received_data.temp);
    double2str(hum_str, received_data.hum);
    LOG_INFO("Received data from ");
    LOG_INFO_LLADDR(src);
    LOG_INFO_(": ID=%u, Count=%u, Temp=%s, Hum=%s\n", received_data.ID, received_data.count, temp_str, hum_str);
  }
}

PROCESS_THREAD(leaf_node_process, ev, data) {
  static struct etimer periodic_timer;
  static unsigned count = 0;

  PROCESS_BEGIN();

#if MAC_CONF_WITH_TSCH
  tsch_set_coordinator(linkaddr_cmp(&coordinator_addr, &linkaddr_node_addr));
#endif // MAC_CONF_WITH_TSCH

  // Initialize NullNet
  nullnet_buf = (uint8_t *)&sensor_data;
  nullnet_len = sizeof(sensor_data);
  nullnet_set_input_callback(input_callback);

  
  sensor_data.ID = (linkaddr_node_addr.u8[0] ) | (linkaddr_node_addr.u8[1] ); 		// Use first and second byte of the MAC address as ID
  sensor_data.count = 0;
  sensor_data.temp = 0;
  sensor_data.hum = 0;

  SENSORS_ACTIVATE(sht11_sensor);

  if(!linkaddr_cmp(&parent_addr, &linkaddr_node_addr)) {
    etimer_set(&periodic_timer, SEND_INTERVAL);
    while(1) {
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
      
      // Read sensor data
      int temp_raw = sht11_sensor.value(SHT11_SENSOR_TEMP);
      int hum_raw = sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
      sensor_data.temp = temperature_int2double(temp_raw);
      sensor_data.hum = humidity_int2double(hum_raw);
      sensor_data.count = count;

      char temp_str[20], hum_str[20];
      double2str(temp_str, sensor_data.temp);
      double2str(hum_str, sensor_data.hum);

      LOG_INFO("Sending data: ID=%u, Count=%u, Temp=%s, Hum=%s to ", sensor_data.ID, sensor_data.count, temp_str, hum_str);
      LOG_INFO_LLADDR(&parent_addr);
      LOG_INFO_("\n");

      memcpy(nullnet_buf, &sensor_data, sizeof(sensor_data));
      nullnet_len = sizeof(sensor_data);

      NETSTACK_NETWORK.output(&parent_addr);
      count++;
      etimer_reset(&periodic_timer);
    }
  }

  PROCESS_END();
}


