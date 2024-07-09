/*------------------------------------------*/
/* Retain */
bool kRetain = true;
bool kNotRetain = false;
/* Username */
String kMQTTusername = 'fotateam';
/* Password */
String kMQTTpassword = '123456';
/* Host that will be connected to  */
String kMQTTtopic = 'broker.emqx.io';
/* Message ID */
String kMQTTclientIdentifier = 'FlutterClient';
/*---------------Update Screen---------------------*/
/* New update topic */
String kNewUpdateTopic = 'FOTA/OTA/NewUpdate';
/* Download Confirmation topic */
String kDownloadConfirmationTopic = 'FOTA/ESP/DownloadConfirmation';
/* UpdateConfirmed to be downloaded topic */
String kConfirmUpdateTopic = 'FOTA/ESP/UpdateConfirmation';
/* UpdateConfirmed to be downloaded topic */
String kMobileDisconnectTopic = 'FOTA/MobileApp/MobileState';
/* Initialize the MQTT  */
String kMQTTinit = 'FOTA/MobileApp/MobileInit';
/* Download Start */
String kUpdateDownloadStart = 'FOTA/ESP/DownloadStart';
/*Download Percentage*/
String kDownloadPercentage = 'FOTA/ESP/DownloadPercentage';
/* Starting to install */
String kStartIntalling = 'FOTA/ESP/StartInstalling';
/* Installation done */
String kInstallationDone = 'FOTA/ESP/DoneInstalling';
/* Installation Failure */
String kInstallationFailure = 'FOTA/ESP/FailedInstalling';
/* Installing percentage */
String kInstallPercentage = 'FOTA/ESP/InstallPercentage';
/*---------------Feature Screen---------------------*/
String kMQTTFeatureESPConfirmationFile = 'FOTA/Features/ESP/ConfirmationFile';
String kMQTTFeatureESPStartDownload = 'FOTA/Features/ESP/DownloadStart';
String kMQTTFeatureESPDownloadPercentage =
    'FOTA/Features/ESP/DownloadPercentage';
String kMQTTFeatureESPDownloadComplete = 'FOTA/Features/ESP/DownloadComplete';
/*---------------------------------------*/
/* Current Speed topic */
String kCurrentSpeedTopic = 'FOTA/MobileApp/RemoteAccess/SpeedControl/CarSpeed';
/* Engine Control Topic */
String kEngineControlTopic = 'FOTA/MobileApp/RemoteAccess/Engine';
/* Feedback from the vehicle */
String kCarEngineFeedbackTopic = 'FOTA/Car/Engine';
/* Limited Speed topic */
String kLimitedSpeedTopic =
    'FOTA/MobileApp/RemoteAccess/SpeedControl/SpeedLimit/value';
/* Lock/UnLock topic */
String kLockUnLockTopic = 'FOTA/MobileApp/RemoteAccess/DoorControl';
/* AC_temp topic */
String kTemperatureTopic = 'FOTA/MobileApp/RemoteAccess/ACcontrol/type';
/* AC_fanspeed topic */
String kFanSpeedTopic = 'FOTA/MobileApp/RemoteAccess/ACcontrol/FanSpeed';
/*Enable_disable topic*/
String kenable_disableemergencyTopic = 'FOTA/MobileApp/Emergency/State';
/* Feedback topic for emergency */
String kEmergencyFeedback = 'FOTA/Car/Emergency/State';
String kEmergencyVehicleTopic = 'FOTA/Car/Emergency/State';
/*---------------Location Screen---------------------*/
String kTopicLocation =
    'FOTA/MobileApp/service/location'; /*---------------------------------------*/
