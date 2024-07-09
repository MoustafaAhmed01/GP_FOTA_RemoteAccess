import 'package:flutter/material.dart';

class AboutTeam extends StatelessWidget {
  static const String id = 'AboutTeam_Screen';

  const AboutTeam({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'About',
          style: TextStyle(fontWeight: FontWeight.bold),
        ),
        centerTitle: true,
      ),
      body: const SingleChildScrollView(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              'Project Abstraction',
              style: TextStyle(
                color: Color(0xFF2F5496),
                fontSize: 22,
                fontWeight: FontWeight.bold,
              ),
            ),
            SizedBox(height: 16),
            Text(
              '     Firmware Over-the-Air (FOTA) is a technology that allows for the remote update of firmware on a device. This can be done without the need to physically connect the device to a computer or other device. FOTA is commonly used to update software on smartphones, tablets, and other mobile devices. It is also being increasingly used to update firmware on cars and other vehicles\n\n       The graduation project mainly consists of two parts:',
              style: TextStyle(fontSize: 16),
            ),
            Text(
              '                        ✦	FOTA \n                        ✦	Vehicle remote access',
              style: TextStyle(
                  fontSize: 16,
                  color: Colors.white70,
                  fontWeight: FontWeight.bold),
            ),
            Text(
              '\nSo, as mentioned, the first part will be building a reliable software update and bug report system between the company and the client (Vehicle).\n       The second part will be adding some features to our vehicle and interfacing with it through a simple mobile app. The vehicle features still vary but, mainly it will include locking and unlocking your car doors, checking on the vehicle’s health, car anti-theft system, speed monitoring, and limiter. There could be more features that could be added, like as said it’s still a variant but, we have mentioned the agreed things till now.',
              style: TextStyle(fontSize: 16),
            ),
            SizedBox(
              height: 20,
            ),
            Text(
              'Main Topics',
              style: TextStyle(
                color: Color(0xFF2F5496),
                fontSize: 22,
                fontWeight: FontWeight.bold,
              ),
            ),
            Text(
              '     ✦ FOTA (Firmware Over-The-Air)',
              style: TextStyle(
                color: Color(0xFF2F5496),
                fontSize: 18,
                fontWeight: FontWeight.w900,
              ),
            ),
            Text(
              'Introduction',
              style: TextStyle(
                color: Color(0xFF1F3763),
                fontSize: 18,
                fontWeight: FontWeight.bold,
              ),
            ),
            Text(
              '     Firmware over-the-air (FOTA) updates have been used in vehicles for over a decade, but they have become increasingly common in recent years as vehicles have become more and more connected. FOTA allows manufacturers to push software updates to vehicles remotely, without the need for drivers to take their vehicles to a dealership. This can be used to fix bugs, improve performance, and add new features.\n\nEarly adopters of FOTA in vehicles include:',
              style: TextStyle(fontSize: 16),
            ),
            Row(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  '    ✦	Volvo: ',
                  style: TextStyle(
                      fontSize: 16,
                      color: Colors.white70,
                      fontWeight: FontWeight.bold),
                ),
                Text(
                  'Volvo was one of the first \nautomakers to offer FOTA \nupdates to its vehicles in 2012.',
                  style: TextStyle(fontSize: 16),
                ),
              ],
            ),
            SizedBox(
              height: 20,
            ),
            Row(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  '    ✦	Tesla: ',
                  style: TextStyle(
                      fontSize: 16,
                      color: Colors.white70,
                      fontWeight: FontWeight.bold),
                ),
                Text(
                  'Tesla has been a leader in \nFOTA updates. It began \noffering over-the-air updates \nto its vehicles in 2012, and it \nnow offers updates regularly \nto improve performance, \nadd new features, and fix bugs',
                  style: TextStyle(fontSize: 16),
                ),
              ],
            ),
            Text(
              '\n     FOTA is becoming increasingly important as vehicles become more and more connected. In the future, FOTA updates will likely be used to add new features and capabilities to vehicles regularly. This will help to keep vehicles up-to-date and ensure that they are equipped with the latest safety and security features.',
              style: TextStyle(fontSize: 16),
            ),
            SizedBox(
              height: 20,
            ),
            Image(
              image: AssetImage('images/FOTA_About_1.png'),
            ),
            SizedBox(height: 20),
            Text(
              '     ✦ Vehicle remote access',
              style: TextStyle(
                color: Color(0xFF2F5496),
                fontSize: 18,
                fontWeight: FontWeight.w900,
              ),
            ),
            Text(
              'Introduction',
              style: TextStyle(
                color: Color(0xFF1F3763),
                fontSize: 18,
                fontWeight: FontWeight.bold,
              ),
            ),
            Text(
              '     Well, on the other hand, let’s start talking about the features that could be added to our vehicle. Car Remote Access offers a diverse range of benefits, including vehicle health reports, remote door locking/unlocking, parking assistance, and emergency assistance. It enhances security, and safety, and provides crucial vehicle health data. The system allows users to contact emergency services and roadside assistance, with the added feature of setting boundaries for teen drivers. Additionally, it offers Stolen Vehicle Location Assistance for more urgent situations, making it a comprehensive and confidence-boosting package for vehicle owners.',
              style: TextStyle(fontSize: 16),
            ),
            SizedBox(height: 16),
            Text(
              'Features',
              style: TextStyle(
                color: Color(0xFF1F3763),
                fontSize: 18,
                fontWeight: FontWeight.bold,
              ),
            ),
            Text(
              '    ✦	Lock/Unlock your vehicle',
              style: TextStyle(
                  fontSize: 16,
                  color: Colors.white70,
                  fontWeight: FontWeight.bold),
            ),
            Text(
              '    ✦	Car anti-theft system',
              style: TextStyle(
                  fontSize: 16,
                  color: Colors.white70,
                  fontWeight: FontWeight.bold),
            ),
            Text(
              '    ✦	Speed limit/Monitoring',
              style: TextStyle(
                  fontSize: 16,
                  color: Colors.white70,
                  fontWeight: FontWeight.bold),
            ),
            Text(
              '    ✦	Check your vehicle’s health',
              style: TextStyle(
                  fontSize: 16,
                  color: Colors.white70,
                  fontWeight: FontWeight.bold),
            ),
            Text(
              '    ✦	Locate your parked location',
              style: TextStyle(
                  fontSize: 16,
                  color: Colors.white70,
                  fontWeight: FontWeight.bold),
            ),
            SizedBox(height: 16),
            Text(
              'Project HW Design',
              style: TextStyle(
                color: Color(0xFF1F3763),
                fontSize: 18,
                fontWeight: FontWeight.bold,
              ),
            ),
            Image(
              image: AssetImage('images/FOTA_About_2.png'),
            ),
            SizedBox(height: 16),
            Text(
              'Contact Us',
              style: TextStyle(
                fontSize: 24,
                fontWeight: FontWeight.bold,
              ),
            ),
            SizedBox(height: 16),
            Text(
              'Email: fotateam@gmail.com\nPhone: +01001445046\nAddress: Cairo University, Giza, Egypt',
              style: TextStyle(fontSize: 16),
            ),
            SizedBox(height: 32),
          ],
        ),
      ),
    );
  }
}
