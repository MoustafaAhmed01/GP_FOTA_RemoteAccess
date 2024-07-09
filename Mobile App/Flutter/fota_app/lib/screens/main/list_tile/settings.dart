import 'package:flutter/material.dart';

class AppSettings extends StatefulWidget {
  static const String id = 'Settings_Screen';

  const AppSettings({super.key});

  @override
  _AppSettingsState createState() => _AppSettingsState();
}

class _AppSettingsState extends State<AppSettings> {
  bool _darkModeEnabled = false;
  String _selectedLanguage = 'English';
  bool _notificationEnabled = true;
  String _selectedNotificationFrequency = 'Daily';

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'Settings',
          style: TextStyle(fontWeight: FontWeight.bold),
        ),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            SwitchListTile(
              title: const Text(
                'Dark Mode',
                style: TextStyle(fontWeight: FontWeight.bold),
              ),
              value: _darkModeEnabled,
              onChanged: (value) {
                setState(() {
                  _darkModeEnabled = value;
                  // Implement logic to change the theme based on _darkModeEnabled
                });
              },
            ),
            const SizedBox(height: 16),
            const Text(
              'Language',
              style: TextStyle(fontWeight: FontWeight.bold, fontSize: 16),
            ),
            const SizedBox(height: 8),
            DropdownButton<String>(
              value: _selectedLanguage,
              onChanged: (value) {
                setState(() {
                  _selectedLanguage = value!;
                  // Implement logic to change the app language based on _selectedLanguage
                });
              },
              items: <String>['English', 'Spanish', 'French']
                  .map<DropdownMenuItem<String>>((String value) {
                return DropdownMenuItem<String>(
                  value: value,
                  child: Text(value),
                );
              }).toList(),
            ),
            const SizedBox(height: 16),
            SwitchListTile(
              title: const Text(
                'Notifications',
                style: TextStyle(fontWeight: FontWeight.bold),
              ),
              value: _notificationEnabled,
              onChanged: (value) {
                setState(() {
                  _notificationEnabled = value;
                  // Implement logic to enable/disable notifications
                });
              },
            ),
            const SizedBox(height: 16),
            const Text(
              'Notification Frequency',
              style: TextStyle(fontWeight: FontWeight.bold, fontSize: 16),
            ),
            const SizedBox(height: 8),
            DropdownButton<String>(
              value: _selectedNotificationFrequency,
              onChanged: (value) {
                setState(() {
                  _selectedNotificationFrequency = value!;
                  // Implement logic to change notification frequency
                });
              },
              items: <String>['Daily', 'Weekly', 'Monthly']
                  .map<DropdownMenuItem<String>>((String value) {
                return DropdownMenuItem<String>(
                  value: value,
                  child: Text(value),
                );
              }).toList(),
            ),
            const SizedBox(height: 32),
            Center(
              child: ElevatedButton(
                onPressed: () {
                  // Implement logic to save settings
                  // For example, you can use shared preferences to persist settings
                },
                child: const Text(
                  'Save Settings',
                  style: TextStyle(fontWeight: FontWeight.bold),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
