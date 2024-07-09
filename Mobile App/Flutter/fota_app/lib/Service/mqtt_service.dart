import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

import '../constants/mqtt_topics.dart';

class MQTTService {
  late MqttServerClient _client;

  MQTTService(String server, String clientIdentifier, String username,
      String password) {
    _client = MqttServerClient(server, clientIdentifier);
    _client.logging(on: true);
    _client.onConnected = onConnected;
    _client.onDisconnected = onDisconnected;
    _client.onSubscribed = onSubscribed;
    _client.onSubscribeFail = onSubscribeFail;
    _client.pongCallback = pong;
    final connMessage = MqttConnectMessage()
        .withClientIdentifier(clientIdentifier)
        .startClean()
        .withWillTopic(kMobileDisconnectTopic)
        .withWillMessage('Disconnected')
        .withWillQos(MqttQos.atLeastOnce)
        // Add username and password for authentication
        .authenticateAs(username, password);
    _client.connectionMessage = connMessage;
  }

  void connect(List<String> topics) async {
    try {
      await _client.connect();
      for (String topic in topics) {
        _client.subscribe(topic, MqttQos.exactlyOnce);
      }
    } catch (e) {
      print('Exception: $e');
      _client.disconnect();
    }
  }

  // Disconnect method to gracefully disconnect from MQTT broker
  void disconnect() {
    _client.disconnect();
  }

  void onConnected() {
    print('Connected');
  }

  void onDisconnected() {
    print('Disconnected');
  }

  void onSubscribed(String topic) {
    print('Subscribed to topic: $topic');
  }

  void onSubscribeFail(String topic) {
    print('Failed to subscribe to topic: $topic');
  }

  void pong() {
    print('Ping response client callback invoked');
  }

  void publishMessage(String topic, String message, bool Retain) {
    final builder = MqttClientPayloadBuilder();
    builder.addString(message);
    _client.publishMessage(topic, MqttQos.exactlyOnce, builder.payload!,
        retain: Retain);
  }

  void listenForUpdates(void Function(String, String) onUpdate) {
    _client.updates?.listen((List<MqttReceivedMessage<MqttMessage>> c) {
      final MqttPublishMessage recMess = c[0].payload as MqttPublishMessage;

      final String payload =
          MqttPublishPayload.bytesToStringAsString(recMess.payload.message);
      onUpdate(c[0].topic, payload);
    });
  }
}
