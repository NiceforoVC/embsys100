# Embedded Device Example

*Using the telegraph example, and the challenges listed in the module as reference, and describe another device that you would like to discuss. Describe how you think its embedded system works, and what design challenges it presents.*

## Device Selected: Nest Learning Thermostat
 	 
An embedded device that is interesting to me is the **Nest Learning Thermostat**, this device is a solution to replace the thermostat unit that comes with the heating/cooling systems that are installed in most houses. The advertised advantage of this device is that it will help the users to have energy savings by “learning” the heating/cooling behaviors of the users. It also provides wifi connectivity and an accompanying app that allows the users to remote control the system settings and keep track of the system usage using their smartphones.

![Image of Nest Learning Thermostat](https://github.com/NiceforoVC/embsys100/blob/master/assignment01/nest_thermostat.png)

### How do you think its embedded system works?

I believe the basic functionality consists of the following:

1.	Monitor the following sensors for operation:
a.	Temperature. 
b.	Humidity.
c.	Occupancy.
d.	Proximity.
e.	Ambient light.
f.	Magnetic. 
2.	The product has an LCD display that serves as the main visual interface to the user, a rotary ring around the display, to change settings, and a button to accept the selections (the button is the ring itself, we just need to push the ring down to depress the button).
3.	The basic operation is to control the output relays that determine the operation of the heating/cooling units to get to the target temperature setpoint. The user can schedule temperature settings for different times during the different days of the week.
4.	The product has software algorithms to “learn” (store) heating/cooling behavior of users, to optimize operation of the system.
5.	Wifi connectivity to access internet services that allow remote operation and tracking of usage.
6.	Bluetooth connectivity to monitor and control additional “slave” devices that control other zones of the house.

### What design challenges it presents?

The challenges this product has are the following:

#### Throughput.
When connected to a network of slave devices the system should have enough processing power to handle communications with all the devices to properly monitor and control them.

#### Testability.
During system validation, the different possible setup combinations should be tested to ensure proper operation of the system. Most likely during the manufacturing process, tests systems of the product need to verify the different outputs and sensors, display operation, and wifi/BT communications.

#### Debuggability.
The main interfaces of the product are through wifi/BT, maybe there’s a way to use physical connectors only available through openings in the case which are not obvious to the end user, or through the base/display connector of the units (debugging base and display separately).

#### Program installation and upgrade.
Initial SW installation most likely happens during manufacturing of the product, but the system should be robust enough to process upgrades over the internet without bricking the unit.

#### Reliability.
The device is controlling one of the critical systems of a house, the heating/cooling unit, and the design needs to be reliable enough to handle unexpected power outages and respond properly to high current draw events (fans misbehaving maybe?).

#### Power consumption.
The product is designed to draw its power from the heating/cooling unit wiring, it also has a lithium battery, so it has to have circuitry to monitor for power outages and the charge level of the battery.

#### Security.
Since the main interface with the user is through wifi, the system needs to have security checks in place to prevent unwanted connections.

#### Cost.
This is a challenge because the device has lots of features in a very small footprint, and the aspect of the product seems to be of high quality. 



