//
//  DJIRemoteController.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <DJISDK/DJIBaseComponent.h>

#define DJI_RC_CONTROL_CHANNEL_SIZE     (4)

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - Data Structs and Enums
/*********************************************************************************/

#pragma pack(1)

//-----------------------------------------------------------------
#pragma mark DJIRemoteControllerMode
//-----------------------------------------------------------------
/**
 *  Remote Controller mode of operation can be normal (single RC connected to aircraft), master,
 *  slave, or unknown.
 */
typedef NS_ENUM (uint8_t, DJIRemoteControllerMode){
    /**
     *  Remote Controller is a master (will route a connected slave Remote Controller's commands to the aircraft).
     */
    DJIRemoteControllerModeMaster,
    /**
     *  Remote Controller is currently a slave Remote Controller (sends commands to aircraft through a master Remote Controller).
     */
    DJIRemoteControllerModeSlave,
    /**
     *  Remote Controller is unconnected to another Remote Controller.
     */
    DJIRemoteControllerModeNormal,
    /**
     *  The Remote Controller's mode is unknown.
     */
    DJIRemoteControllerModeUnknown,
};

//-----------------------------------------------------------------
#pragma mark DJIRCID
//-----------------------------------------------------------------
/**
 *  Remote Controller's unique identification number. This is given to each Remote
 *  Controller during manufacturing and cannot be changed.
 */
typedef uint32_t DJIRCID;

//-----------------------------------------------------------------
#pragma mark DJIRCSignalQualityOfConnectedRC
//-----------------------------------------------------------------
/**
 *  Signal quality of a connected master or slave Remote Controller in percent [0, 100].
 */
typedef uint8_t DJIRCSignalQualityOfConnectedRC;

//-----------------------------------------------------------------
#pragma mark DJIRCControlStyle
//-----------------------------------------------------------------
/**
 *  Remote Controller's control style.
 */
typedef NS_OPTIONS (uint8_t, DJIRCControlStyle){
    /**
     *  Remote Controller uses Japanese controls (also known as Mode 1). In this mode the left stick controls Pitch
     *  and Yaw, and the right stick controls Throttle and Roll.
     */
    RCControlStyleJapanese,
    /**
     *  Remote Controller uses American controls (also known as Mode 2). In this mode
     *  the left stick controls Throttle and Yaw, and the right stick controls Pitch and Roll.
     */
    RCControlStyleAmerican,
    /**
     *  Remote Controller uses Chinese controls (also know as Mode 3). In this mode the left stick controls Pitch and Roll, and the right stick controls Throttle and Yaw.
     */
    RCControlStyleChinese,
    /**
     *  Stick channel mapping for Roll, Pitch, Yaw and Throttle can be customized.
     */
    RCControlStyleCustom,
    /**
     *  Default Remote Controller controls and settings for the slave
     *  Remote Controller.
     */
    RCSlaveControlStyleDefault,
    /**
     *  Slave remote controller stick channel mapping for Roll, Pitch, Yaw and
     *  Throttle can be customized.
     */
    RCSlaveControlStyleCustom,
    /**
     *  The Remote Controller's control style is
     *  unknown.
     */
    RCControlStyleUnknown,
};

//-----------------------------------------------------------------
#pragma mark DJIRCControlChannelName
//-----------------------------------------------------------------
/**
 *  Remote Controller control channels. These will be used in RC Custom Control Style. See
 *  `RCControlStyleCustom` and `RCSlaveControlStyleCustom` for more information.
 *
 */
typedef NS_ENUM (uint8_t, DJIRCControlChannelName){
    /**
     *  Throttle control channel.
     */
    DJIRCControlChannelNameThrottle,
    /**
     *  Pitch control channel.
     */
    DJIRCControlChannelNamePitch,
    /**
     *  Roll control channel.
     */
    DJIRCControlChannelNameRoll,
    /**
     *  Yaw control channel.
     */
    DJIRCControlChannelNameYaw,
};

//-----------------------------------------------------------------
#pragma mark DJIRCControlChannel
//-----------------------------------------------------------------
/**
 *  Remote Controller's control channel.
 */
typedef struct
{
    /**
     *  Name of the control channel. The format of this
     *  is `DJI_RC_CONTROL_CHANNEL_xxx`. The default is American.
     */
    DJIRCControlChannelName channel;
    /**
     *  The control channel's settings will be reversed.
     *  For example, for the throttle, the joystick is moved up or
     *  down. If the control channel was reversed, the same motion
     *  that was once used for up would now move the aircraft
     *  down, and the same motion that was once used for down would
     *  now move the aircraft up.
     */
    BOOL reverse;
} DJIRCControlChannel;

//-----------------------------------------------------------------
#pragma mark DJIRCControlMode
//-----------------------------------------------------------------
/**
 *  Remote Controller's control mode.
 */
typedef struct
{
    /**
     *  The control style to which the Remote Controller is set.
     */
    DJIRCControlStyle controlStyle;
    /**
     *  Setting controls for each of the channels.
     */
    DJIRCControlChannel controlChannel[DJI_RC_CONTROL_CHANNEL_SIZE];
} DJIRCControlMode;

//-----------------------------------------------------------------
#pragma mark DJIRCRequestGimbalControlResult
//-----------------------------------------------------------------
/**
 *  Result when a slave Remote Controller requests permission to control the gimbal.
 */
typedef NS_OPTIONS (uint8_t, DJIRCRequestGimbalControlResult){
    /**
     *  The master Remote Controller agrees to the slave's request.
     */
    RCRequestGimbalControlResultAgree,
    /**
     *  The master Remote Controller denies the slave's request. If the slave Remote Controller wants to control the
     *  gimbal, it must send a request to the master Remote Controller first. Then the master Remote Controller can decide to
     *  approve or deny the request.
     */
    RCRequestGimbalControlResultDeny,
    /**
     *  The slave Remote Controller's request timed out.
     */
    RCRequestGimbalControlResultTimeout,
    /**
     *  The master Remote Controller authorized the slave request to control the gimbal.
     */
    RCRequestGimbalControlResultAuthorized,
    /**
     *  The slave Remote Controller's request is unknown.
     */
    RCRequestGimbalControlResultUnknown,
};

//-----------------------------------------------------------------
#pragma mark DJIRCControlPermission
//-----------------------------------------------------------------
/**
 *  Remote Controller's control permission.
 */
typedef struct
{
    /**
     *  TRUE if the Remote Controller has permission
     *  to control the gimbal yaw.
     */
    bool hasGimbalYawControlPermission;
    /**
     *  TRUE if the Remote Controller has permission
     *  to control the gimbal roll.
     */
    bool hasGimbalRollControlPermission;
    /**
     *  TRUE if the Remote Controller has permission
     *  to control the gimbal pitch.
     */
    bool hasGimbalPitchControlPermission;
    /**
     *  TRUE if the Remote Controller has permission
     *  to control camera playback.
     */
    bool hasPlaybackControlPermission;
    /**
     *  TRUE if the Remote Controller has permission
     *  to record video with the camera.
     */
    bool hasRecordControlPermission;
    /**
     *  TRUE if the Remote Controller has permission
     *  to take pictures with the camera.
     */
    bool hasCaptureControlPermission;
} DJIRCControlPermission;

//-----------------------------------------------------------------
#pragma mark DJIRCGimbalControlSpeed
//-----------------------------------------------------------------
/**
 *  Remote Controller's gimbal control speed.
 */
typedef struct
{
    /**
     *  Gimbal's pitch speed with range [0,100].
     */
    uint8_t pitchSpeed;
    /**
     *  Gimbal's roll speed with range [0,100].
     */
    uint8_t rollSpeed;
    /**
     *  Gimbal's yaw speed with range [0,100].
     */
    uint8_t yawSpeed;
} DJIRCGimbalControlSpeed;

//-----------------------------------------------------------------
#pragma mark DJIRCToAircraftPairingState
//-----------------------------------------------------------------
/**
 *  Remote Controller pairing state.
 */
typedef NS_ENUM (uint8_t, DJIRCToAircraftPairingState){
    /**
     *  The Remote Controller is not pairing.
     */
    DJIRCToAircraftPairingStateNotParing,
    /**
     *  The Remote Controller is currently pairing.
     */
    DJIRCToAircraftPairingStateParing,
    /**
     *  The Remote Controller's pairing was completed.
     */
    DJIRCToAircraftPairingStateCompleted,
    /**
     *  The Remote Controller's pairing state is unknown.
     */
    DJIRCToAircraftPairingStateUnknown,
};

//-----------------------------------------------------------------
#pragma mark DJIRCJoinMasterResult
//-----------------------------------------------------------------
/**
 *  Result when a slave Remote Controller tries to join
 *  a master Remote Controller.
 */
typedef NS_ENUM (uint8_t, DJIRCJoinMasterResult){
    /**
     *  The slave Remote Controller's attempt to join
     *  the master Remote Controller was successful.
     */
    DJIRCJoinMasterResultSuccessful,
    /**
     *  The slave Remote Controller's attempt to join
     *  the master Remote Controller was unsuccessful
     *  due to a password error.
     */
    DJIRCJoinMasterResultPasswordError,
    /**
     *  The slave Remote Controller's attempt to join
     *  the master Remote Controller was rejected.
     */
    DJIRCJoinMasterResultRejected,
    /**
     *  The slave Remote Controller's attempt to join
     *  the master Remote Controller was unsuccesful
     *  because the master Remote Controller is at the
     *  maximum number of slaves it can have.
     */
    DJIRCJoinMasterResultReachMaximum,
    /**
     *  The slave Remote Controller's attempt to join
     *  the master Remote Controller was unsuccessful
     *  because the request timed out.
     */
    DJIRCJoinMasterResultResponseTimeout,
    /**
     *  The result of the slave Remote Controller's
     *  attempt to join the master Remote Controller
     *  is unknown.
     */
    DJIRCJoinMasterResultUnknown
};

//-----------------------------------------------------------------
#pragma mark DJIRCBatteryInfo
//-----------------------------------------------------------------
/**
 *  Remote Controller's battery info.
 */
typedef struct
{
    /**
     *  The remaining power in the Remote Controller's
     *  battery in milliamp hours (mAh).
     */
    uint32_t remainingEnergyInMAh;
    /**
     *  The remaining power in the Remote Controller's
     *  battery as a percentage in the range of [0, 100].
     */
    uint8_t remainingEnergyInPercent;
} DJIRCBatteryInfo;

//-----------------------------------------------------------------
#pragma mark DJIRCGpsTime
//-----------------------------------------------------------------
/**
 *  Remote Controller's GPS time.
 */
typedef struct
{
    /**
     *  Hour value of Remote Controller's GPS time.
     */
    uint8_t hour;
    /**
     *  Minute value of Remote Controller's GPS time.
     */
    uint8_t minute;
    /**
     *  Second value of Remote Controller's GPS time.
     */
    uint8_t second;
    /**
     *  Year value of Remote Controller's GPS time.
     */
    uint16_t year;
    /**
     *  Month value of Remote Controller's GPS time.
     */
    uint8_t month;
    /**
     *  Day value of Remote Controller's GPS time.
     */
    uint8_t day;
} DJIRCGpsTime;

//-----------------------------------------------------------------
#pragma mark DJIRCGPSData
//-----------------------------------------------------------------
/**
 *  Remote Controller's GPS data. Only Inspire and M100 Remote Controllers have GPS.
 */
typedef struct
{
    /**
     *  The Remote Controller's GPS time.
     */
    DJIRCGpsTime time;
    /**
     *  The Remote Controller's GPS latitude
     *  in degrees.
     */
    double latitude;
    /**
     *  The Remote Controller's GPS longitude
     *  in degrees.
     */
    double longitude;
    /**
     *  The Remote Controller's speed in the East
     *  direction in meters/second. A negative speed means the Remote Controller is moving in the West direction.
     */
    float speedEast;
    /**
     *  The Remote Controller's speed in the North
     *  direction in meters/second. A negative speed means the Remote Controller is moving in the South direction.
     */
    float speedNorth;
    /**
     *  The number of GPS sattelites the Remote Controller detects.
     */
    int satelliteCount;
    /**
     *  The the margin of error, in meters, for the
     *  GPS location.
     */
    float accuracy;
    /**
     *  YES if the GPS data is valid. The data is not valid if there are too few satellites or the signal strength is too low.
     */
    BOOL isValid;
} DJIRCGPSData;

//-----------------------------------------------------------------
#pragma mark DJIRCGimbalControlDirection
//-----------------------------------------------------------------
/**
 *  Defines what the Gimbal Dial (upper left wheel on the Remote Controller) will control.
 */
typedef NS_ENUM (uint8_t, DJIRCGimbalControlDirection){
    /**
     *  The upper left wheel will control the gimbal's pitch.
     */
    DJIRCGimbalControlDirectionPitch,
    /**
     *  The upper left wheel will control the gimbal's roll.
     */
    DJIRCGimbalControlDirectionRoll,
    /**
     *  The upper left wheel will control the gimbal's yaw.
     */
    DJIRCGimbalControlDirectionYaw,
};

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareRightWheel
//-----------------------------------------------------------------
/**
 *  Current state of the Camera Settings Dial (upper right wheel on the Remote Controller).
 */
typedef struct
{
    /**
     * YES if right wheel present.
     */
    BOOL isPresent;
    /**
     *  YES if wheel value has changed.
     */
    BOOL wheelChanged;
    /**
     *  YES if wheel is being pressed.
     */
    BOOL wheelButtonDown;
    /**
     *  YES if wheel is being turned in a clockwise direction.
     */
    BOOL wheelDirection;
    /**
     *  Wheel value in the range of [0, 1320]. The value represents the difference in an operation.
     */
    uint8_t value;
} DJIRCHardwareRightWheel;

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareLeftWheel
//-----------------------------------------------------------------
/**
 *  Remote Controller's left wheel.
 */
typedef struct
{
    /**
     *  Gimbal Dial's (upper left wheel) value in the range of [-660,660], where 0 is untouched and positive is turned in the clockwise direction.
     */
    int value;
} DJIRCHardwareLeftWheel;

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareTransformationSwitchState
//-----------------------------------------------------------------
/**
 *  Transformation Switch position states.
 */
typedef NS_ENUM (uint8_t, DJIRCHardwareTransformationSwitchState){
    /**
     *  Retract landing gear switch state.
     */
    DJIRCHardwareTransformationSwitchStateRetract,
    /**
     *  Deploy landing gear switch state.
     */
    DJIRCHardwareTransformationSwitchStateDeploy
};

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareTransformSwitch
//-----------------------------------------------------------------
/**
 *  Transformation Switch position. The Transformation Switch is around the Return To Home Button on Inspire, Inspire 1 and M100 Remote Controllers, and controls the state of the aircraft's landing gear.
 */
typedef struct
{
    /**
     *  YES if the Transformation Switch present.
     */
    BOOL isPresent;
    /**
     *  Current transformation switch state.
     */
    DJIRCHardwareTransformationSwitchState transformationSwitchState;
    
} DJIRCHardwareTransformationSwitch;

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareFlightModeSwitchState
//-----------------------------------------------------------------
/**
 *  Remote Controller Flight Mode Switch State
 */
typedef NS_ENUM (uint8_t, DJIRCHardwareFlightModeSwitchState){
    /**
     *  The Remote Controller's flight mode switch is set to the F (Function) mode. For the Phantom 3, Inspire 1 and M100 the remote controller must be in Function mode to enable Mission Manager functions from the Mobile Device. It is not supported by Phantom 4 (which must use P mode for the Mission Manager functions).
     *  The Phantom 4 remote controller flight mode switch is labelled A, S, P from left to right.
     *  The Phantom 3, Inspire 1 and M100 remote controller flight mode switch is labelled F, A, P from left to right.
     *  Independent of label, any remote controller (P3, P4, Inspire 1, M100) used with the Phantom 3, Inspire 1 or M100 will report F mode as selected if the switch is set to the left position.
     */
    DJIRCHardwareFlightModeSwitchStateF,
    /**
     *  The Remote Controller's flight mode switch is set to the A (Attitude) mode. Attitude mode does not use GPS and the vision system for hovering or flying, but uses the barometer to maintain alititude. If the GPS signal is strong enough, the aircraft can still return to home in this mode.
     *  The Phantom 4 remote controller flight mode switch is labelled A, S, P from left to right.
     *  The Phantom 3, Inspire 1 and M100 remote controller flight mode switch is labelled F, A, P from left to right.
     *  Independent of label, any remote controller (P3, P4, Inspire 1, M100) used with the Phantom 4 will report A mode as selected if the switch is set to the left position.
     *  Independent of label, any remote controller (P3, P4, Inspire 1, M100) used with the Phantom 3, Inspire 1 or M100 will report A mode as selected if the switch is set to the middle position.
     */
    DJIRCHardwareFlightModeSwitchStateA,
    /**
     *  The Remote Controller's flight mode switch is set to the P (Positioning) mode. Positioning mode can use both GPS and the vision system (when available) to fly and hover. For the Phantom 4, P mode must be used to enable Mission Manager functions from the Mobile Device.
     *  The Phantom 4 remote controller flight mode switch is labelled A, S, P from left to right.
     *  The Phantom 3, Inspire 1 and M100 remote controller flight mode switch is labelled F, A, P from left to right.
     *  Any remote controller (P3, P4, Inspire 1, M100) used with any aircraft will report P mode as selected if the switch is set to the right position.
     */
    DJIRCHardwareFlightModeSwitchStateP,
    /**
     *  The Remote Controller's flight mode switch is set to the S (Sport) mode. Sport mode can use both GPS and the vision system (when available) to hover. Sport mode is only supported when using the Phantom 4.
     The Phantom 4 remote controller flight mode switch is labelled A, S, P from left to right.
     The Phantom 3, Inspire 1 and M100 remote controller flight mode switch is labelled F, A, P from left to right.
     Independent of label, any remote controller (P3, P4, Inspire 1, M100) used with the Phantom 4 will report S mode as selected if the switch is set to the middle position.
     */
    DJIRCHardwareFlightModeSwitchStateS
};

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareFlightModeSwitch
//-----------------------------------------------------------------
/**
 *  The value of the Remote Controller's flight mode switch.
 */
typedef struct
{
    /**
     *  Value of the Remote Controller's flight mode switch.
     */
    DJIRCHardwareFlightModeSwitchState mode;
} DJIRCHardwareFlightModeSwitch;

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareButton
//-----------------------------------------------------------------
/**
 *  Remote Controller has numerous momentary push buttons, which will use this state.
 */
typedef struct
{
    /**
     * YES if Hardware button present.
     */
    BOOL isPresent;
    /**
     *  YES if button is pressed down.
     */
    BOOL buttonDown;
} DJIRCHardwareButton;

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareJoystick
//-----------------------------------------------------------------
/**
 *  Remote Controller's joystick
 */
typedef struct
{
    /**
     *  Joystick's channel value in the range of [-660, 660]. This
     *  value may be different for the aileron, elevator, throttle, and rudder.
     */
    int value;
} DJIRCHardwareJoystick;

//-----------------------------------------------------------------
#pragma mark DJIRCHardwareState
//-----------------------------------------------------------------
/**
 *  Remote Controller's current state.
 */
typedef struct
{
    /**
     *  Left joystick 's horizontal value.
     */
    DJIRCHardwareJoystick leftHorizontal;
    /**
     *  Left joystick 's vertical value.
     */
    DJIRCHardwareJoystick leftVertical;
    /**
     *  Right joystick 's Vertical value.
     */
    DJIRCHardwareJoystick rightVertical;
    /**
     *  Right joystick 's Horizontal value.
     */
    DJIRCHardwareJoystick rightHorizontal;
    /**
     *  Current state of the upper left wheel on the Remote Controller (Gimbal Dial).
     */
    DJIRCHardwareLeftWheel leftWheel;
    /**
     *  Current state of the upper right wheel on the Remote Controller (Camera Settings Dial).
     */
    DJIRCHardwareRightWheel rightWheel;
    /**
     *  Current state of the Transformation Switch on the Remote Controller.
     */
    DJIRCHardwareTransformationSwitch transformationSwitch;
    /**
     *  Current state of the Flight Mode Switch on the Remote Controller.
     */
    DJIRCHardwareFlightModeSwitch flightModeSwitch;
    /**
     *  Current state of the Return To Home Button.
     */
    DJIRCHardwareButton goHomeButton;
    /**
     *  Current state of the Video Recording Button.
     */
    DJIRCHardwareButton recordButton;
    /**
     *  Current state of the Shutter Button.
     */
    DJIRCHardwareButton shutterButton;
    /**
     *  Current state of the Playback Button. The Playback Button is not supported on Phantom 4 remote controllers.
     */
    DJIRCHardwareButton playbackButton;
    /**
     *  Current state of the Pause Button. The Pause button is only supported on Phantom 4 remote controllers.
     */
    DJIRCHardwareButton pauseButton;
    /**
     *  Current state of custom button 1 (left Back Button).
     */
    DJIRCHardwareButton customButton1;
    /**
     *  Current state of custom button 2 (right Back Button).
     */
    DJIRCHardwareButton customButton2;
} DJIRCHardwareState;

//-----------------------------------------------------------------
#pragma mark DJIRCRemoteFocusControlType
//-----------------------------------------------------------------
/**
 *  Remote Focus Control Type
 */
typedef NS_ENUM (uint8_t, DJIRCRemoteFocusControlType){
    /**
     *  Control Aperture.
     */
    DJIRCRemoteFocusControlTypeAperture,
    /**
     *  Control Focal Length.
     */
    DJIRCRemoteFocusControlTypeFocalLength,
};

//-----------------------------------------------------------------
#pragma mark DJIRCRemoteFocusControlDirection
//-----------------------------------------------------------------
/**
 *  Remote Focus Control Direction
 */
typedef NS_ENUM (uint8_t, DJIRCRemoteFocusControlDirection){
    /**
     *  Clockwise
     */
    DJIRCRemoteFocusControlDirectionClockwise,
    /**
     *  CounterClockwise
     */
    DJIRCRemoteFocusControlDirectionCounterClockwise,
};

//-----------------------------------------------------------------
#pragma mark DJIRCRemoteFocusState
//-----------------------------------------------------------------
/**
 Remote Controller's Remote Focus State
 
 The focus product has one dial (focus control) that controls two separate parts
 of the camera: focal length and aperture. However it can only control one of
 these at any one time and is an aboslute dial, meaning that a specific rotational
 position of the dial corresponds to a specific focal length or aperture.
 
 This means that whenever the dial control mode is changed, the dial first has to be
 reset to the new mode's previous dial position before the dial can be used to adjust
 the setting of the new mode.
 
 Example workflow:<br/><ol>
 <li>Use dial to set an Aperture of f2.2</li>
 <li>Change dial control mode to focal length (set `DJIRCRemoteFocusControlType`)</li>
 <li>Use the dial to change the focal length</li>
 <li>Change dial control mode back to aperture<ul>
 <li>set `DJIRCRemoteFocusControlType`</li>
 <li>`isFocusControlWorks` will now be NO</li>
 </ul>
 </li>
 <li>Adjust dial back to f2.2<ul>
 <li>`DJIRCRemoteFocusControlDirection` is the direction the dial should be rotated</li>
 <li>`isFocusControlWorks` will become YES when set back to f2.2</li>
 </ul>
 </li>
 <li>Now the dial can be used to adjust the aperture.
 </ol>
 
 */
typedef struct
{
    /**
     *
     *  YES if the focus control works. The control can be either changing the Aperture or Focal Length. If it is NO, follow the `DJIRCRemoteFocusControlDirection` to rotate the Remote Focus Device until it turns to YES again.
     */
    BOOL isFocusControlWorks;
    /**
     *
     *  Remote Focus Control Type
     */
    DJIRCRemoteFocusControlType controlType;
    /**
     *
     *  Remote Focus Control Direction. Use this with the `isFocusControlWorks` value. It will give you the correct rotation direction when `isFocusControlWorks` is NO.
     */
    DJIRCRemoteFocusControlDirection direction;
    
} DJIRCRemoteFocusState;

#pragma pack()

/*********************************************************************************/
#pragma mark - DJIRCInfo
/*********************************************************************************/

/**
 *  This class contains the information for a remote controller.
 */
@interface DJIRCInfo : NSObject

/**
 *  Remote Controller's unique identifier.
 */
@property(nonatomic, assign) DJIRCID identifier;

/**
 *  Remote Controller's name.
 */
@property(nonatomic, strong) NSString *_Nullable name;

/**
 *  Remote Controller's password.
 */
@property(nonatomic, strong) NSString *_Nullable password;

/**
 *  Signal quality of a conneected master or slave Remote Controller.
 */
@property(nonatomic, assign) DJIRCSignalQualityOfConnectedRC signalQuality;

/**
 *  Remote Controller's control permissions.
 */
@property(nonatomic, assign) DJIRCControlPermission controlPermission;

/**
 *  Converts the Remote Controller's unique identifier from the property `identifier` to a string.
 *
 *  @return Remote Controller's identifier as a string.
 */
- (NSString *)RCIdentifier;

@end

/*********************************************************************************/
#pragma mark - DJIRemoteControllerDelegate
/*********************************************************************************/

@class DJIRemoteController;

/**
 *  This protocol provides delegate methods to receive the updated information related to the remote controller.
 *
 *
 */
@protocol DJIRemoteControllerDelegate <NSObject>

@optional

/**
 *  Callback function that updates the Remote Controller's current hardware state (e.g. the state of the physical buttons and joysticks).
 *
 *  @param rc    Instance of the Remote Controller for which the hardware state will be updated.
 *  @param state Current state of the Remote Controller's hardware state.
 */
- (void)remoteController:(DJIRemoteController *)rc didUpdateHardwareState:(DJIRCHardwareState)state;

/**
 *  Callback function that updates the Remote Controller's current GPS data.
 *
 *  @param rc    Instance of the Remote Controller for which the GPS data will be updated.
 *  @param state Current state of the Remote Controller's GPS data.
 */
- (void)remoteController:(DJIRemoteController *)rc didUpdateGpsData:(DJIRCGPSData)gpsData;

/**
 *  Callback function that updates the Remote Controller's current battery state.
 *
 *  @param rc    Instance of the Remote Controller for which the battery state will be updated.
 *  @param state Current state of the Remote Controller's battery state.
 */
- (void)remoteController:(DJIRemoteController *)rc didUpdateBatteryState:(DJIRCBatteryInfo)batteryInfo;

/**
 *  Callback function that gets called when a slave Remote Controller makes a request to a master
 *  Remote Controller to control the gimbal using the method requestGimbalControlRightWithCallbackBlock.
 *
 *  @param rc    Instance of the Remote Controller.
 *  @param state Information of the slave making the request to the master Remote Controller.
 */
- (void)remoteController:(DJIRemoteController *)rc didReceiveGimbalControlRequestFromSlave:(DJIRCInfo *)slave;

/**
 *  Callback function that updates the Remote Focus State, only support Focus product. If the isRCRemoteFocusCheckingSupported is YES, this delegate method will be called.
 *
 *  @param rc    Instance of the Remote Controller for which the battery state will be updated.
 *  @param state Current state of the Remote Focus state.
 */
- (void)remoteController:(DJIRemoteController *)rc didUpdateRemoteFocusState:(DJIRCRemoteFocusState)remoteFocusState;

@end

/*********************************************************************************/
#pragma mark - DJIRemoteController
/*********************************************************************************/

@class DJIWiFiLink;

/**
 This class represents the remote controller of the aircraft. It provides mothods to change the settings of the physical remote controller. For some products (e.g. Inspire 1 and Matric 100), the class provides methods to manager the slave/master mode of the remote controllers.
 
 A remote controller is a device that can have a GPS, battery, radio, buttons, sticks, wheels, and output ports for video. The mobile device is connected to the remote controller, which is always sending out information about what everything is doing. The normal remote controller is called the master. A slave wirelessly connects to the master remote controller at 5 GHz, and the aircraft can also download information to the slave. The slave can send gimbal control commands to the master. This configuration allows one person to fly the aircraft while another person controls the gimbal.
 */
@interface DJIRemoteController : DJIBaseComponent

/**
 *  Returns the delegate of Remote Controller.
 */
@property(nonatomic, weak) id<DJIRemoteControllerDelegate> delegate;

/**
 *  Query method to check if the Remote Controller supports Remote Focus State Checking.
 */
- (BOOL)isRCRemoteFocusCheckingSupported;

/**
 *  Sets the Remote Controller's name.
 *
 *  @param name  Remote controller name to be set. Six characters at most.
 *  @param completion Completion block.
 */
- (void)setRCName:(NSString *_Nonnull)name withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the Remote Controller's name.
 *
 */
- (void)getRCNameWithCompletion:(void (^)(NSString *_Nullable name, NSError *_Nullable error))completion;

/**
 *  Sets the Remote Controller's password.
 *
 *  @param password password Remote controller password to be set, using a string consisted by 4 digits.
 *  @param block    Completion block.
 */
- (void)setRCPassword:(NSString *_Nonnull)password withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the Remote Controller's password.
 *
 */
- (void)getRCPasswordWithCompletion:(void (^)(NSString *_Nullable password, NSError *_Nullable error))completion;

/**
 *  Sets the Remote Controller's control mode.
 *
 *  @param mode  Remote Controller control mode to be set.
 *  @param completion Completion block.
 */
- (void)setRCControlMode:(DJIRCControlMode)mode withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the master Remote Controller's control mode.
 *
 */
- (void)getRCControlModeWithCompletion:(void (^)(DJIRCControlMode mode, NSError *_Nullable error))completion;

//-----------------------------------------------------------------
#pragma mark RC pairing
//-----------------------------------------------------------------
/**
 *  Enters pairing mode, in which the Remote Controller starts pairing with the aircraft.
 *  This method is used when the Remote Controller no longer recognizes which aircraft
 *  it is paired with.
 */
- (void)enterRCToAircraftPairingModeWithCompletion:(DJICompletionBlock)completion;

/**
 *  Exits pairing mode.
 *
 */
- (void)exitRCToAircraftPairingModeWithCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the pairing status as the Remote Controller is pairing with the aircraft.
 *
 */
- (void)getRCToAircraftPairingStateWithCompletion:(void (^)(DJIRCToAircraftPairingState state, NSError *_Nullable error))completion;

//-----------------------------------------------------------------
#pragma mark RC gimbal control
//-----------------------------------------------------------------
/**
 *  Sets the gimbal's pitch speed for the Remote Controller's upper left wheel (Gimbal Dial).
 *
 *  @param speed Speed to be set for the gimbal's pitch, which should in the range of [0, 100],
 *  where 0 represents very slow and 100 represents very fast.
 *  @param completion Completion block.
 */
- (void)setRCWheelGimbalSpeed:(uint8_t)speed withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the gimbal's pitch speed for the Remote Controller's upper left wheel (Gimbal Dial).
 *
 */
- (void)getRCWheelGimbalSpeedWithCompletion:(void (^)(uint8_t speed, NSError *_Nullable error))completion;

/**
 *  Sets which of the gimbal directions the top left wheel (Gimbal Dial) on the Remote Controller will control. The
 *  three options (pitch, roll, and yaw) are outlined in the enum named DJIRCGimbalControlDirection
 *  in DJIRemoteControllerDef.h.
 *
 *  @param direction Gimbal direction to be set that the top left wheel on the Remote Controller
 *  will control.
 *  @param completion Completion block.
 */
- (void)setRCControlGimbalDirection:(DJIRCGimbalControlDirection)direction withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets which of the gimbal directions the top left wheel (Gimbal Dial) on the Remote Controller will control.
 *
 */
- (void)getRCControlGimbalDirectionWithCompletion:(void (^)(DJIRCGimbalControlDirection direction, NSError *_Nullable error))completion;

//-----------------------------------------------------------------
#pragma mark RC custom buttons
//-----------------------------------------------------------------
/**
 *  Sets custom button's (Back Button's) tags, which can be used by the user to record user settings for a particular Remote Controller. Unlike all other buttons, switches and sticks on the Remote Controller, the custom buttons only send state to the Mobile Device and not the aircraft.
 *
 *  @param tag1   Button 1's custom tag.
 *  @param tag2   Button 2's custom tag.
 *  @param completion Completion block.
 */
- (void)setRCCustomButton1Tag:(uint8_t)tag1 customButton2Tag:(uint8_t)tag2 withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the custom button's (Back Button's) tags.
 *
 */
- (void)getRCCustomButtonTagWithCompletion:(void (^)(uint8_t tag1, uint8_t tag2, NSError *_Nullable error))completion;

/**
 *  Set C1 button enable binding DJI GO app state. If it's enable, when user presses the C1 button, an alertView will pop up and ask if you want to open the DJI GO app. This feature only supports MFI certificated Remote Controller.
 
 *  @attention This feature will affect the user of DJI GO app, we suggest you to call this interface to enable the C1 binding feature when your application enter background. Otherwise the C1 button will be unbound with DJI GO app forever.
 *
 *  @param enable Enable C1 button bind DJI GO app.
 *  @param completion Completion block.
 */
- (void) setRCC1ButtonBindingEnabled:(BOOL)enable withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the C1 button enable binding DJI Go app state. This feature only supports MFI certificated Remote Controller.
 *
 */
- (void) getRCC1ButtonBindingEnabledWithCompletion:(void(^_Nullable)(BOOL enable, NSError * _Nullable error))completion;

//----------------------------------------------------------------
#pragma mark RC master and slave mode
//-----------------------------------------------------------------

/**
 *  Query method to check if the Remote Controller supports master/slave mode.
 */
- (BOOL)isMasterSlaveModeSupported;

/**
 *  Sets the Remote Controller's mode. See the `DJIRemoteControllerMode` enum for all possible Remote Controller modes.
 *  The master and slave modes are only supported for the Inspire 1, Inspire 1 Pro and M100.
 *
 *  @param mode  Mode of type `DJIRemoteControllerMode` to be set for the Remote Controller.
 *  @param completion Completion block.
 */
- (void)setRemoteControllerMode:(DJIRemoteControllerMode)mode withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the Remote Controller's mode.
 *
 */
- (void)getRemoteControllerModeWithCompletion:(void (^)(DJIRemoteControllerMode mode, BOOL isConnected, NSError *_Nullable error))completion;

//-----------------------------------------------------------------
#pragma mark RC master and slave mode - Slave RC methods
//-----------------------------------------------------------------

/**
 *  Used by a slave Remote Controller to join a master Remote Controller. If the master Remote Controller accepts the request, the master Remote Controller will control the aircraft, and the slave Remote Controller will control the gimbal and/or be able to view the downlink video.
 *
 *  @param hostId   Master's unique identifier.
 *  @param name     Master's name.
 *  @param password Master's password.
 *  @param block    Remote execution result callback block.
 */
- (void)joinMasterWithID:(DJIRCID)masterId masterName:(NSString *_Nonnull)masterName masterPassword:(NSString *_Nonnull)masterPassword withCompletion:(void (^)(DJIRCJoinMasterResult result, NSError *_Nullable error))completion;

/**
 *  Returns the master Remote Controller's information, which includes the unique identifier, name, and password.
 *
 */
- (void)getJoinedMasterNameAndPassword:(void (^)(DJIRCID masterId, NSString *_Nullable masterName, NSString *_Nullable masterPassword, NSError *_Nullable error))completion;

/**
 *  Starts a search by slave Remote Controller for nearby master Remote Controllers. To get the list of master Remote Controllers, first call `getAvailableMastersWithCallbackBlock`, then call `stopMasterRCSearchWithCompletion` to end the search.
 *
 */
- (void)startMasterRCSearchWithCompletion:(DJICompletionBlock)completion;

/**
 *  Returns all available master Remote Controllers that are located nearby. Before this method can be used, call `startMasterRCSearchWithCompletion` to start the search for master Remote Controllers. Once the list of masters is received, call `stopMasterRCSearchWithCompletion` to end the search.
 *
 */
- (void)getAvailableMastersWithCompletion:(void (^)(NSArray<DJIRCInfo *> *masters, NSError *_Nullable error))completion;

/**
 *  Used by a slave Remote Controller to stop the search for nearby master Remote Controllers.
 *
 */
- (void)stopMasterRCSearchWithCompletion:(DJICompletionBlock)completion;

/**
 *  Returns the state of the master Remote Controller search. The search is initiated by the Mobile Device, but performed by the Remote Controller. Therefore, if the Mobile Device's application crashes while a search is ongoing, this method can be used to let the new instance of the application understand the Remote Controller state.
 *
 */
- (void)getMasterRCSearchStateWithCompletion:(void (^)(BOOL isStarted, NSError *_Nullable error))completion;

/**
 *  Removes a master Remote Controller from the current slave Remote Controller.
 *
 *  @param masterId The connected master's identifier.
 *  @param completion Completion block.
 */
- (void)removeMaster:(DJIRCID)masterId withCompletion:(DJICompletionBlock)completion;

/**
 *  Called by the slave Remote Controller to request gimbal control from the master Remote Controller.
 * s
 */
- (void)requestGimbalControlRightWithCompletion:(void (^)(DJIRCRequestGimbalControlResult result, NSError *_Nullable error))completion;

/**
 *  Sets the Remote Contoller's slave control mode.
 *
 *  @param mode  Control mode to be set. the mode's style should be `RCSlaveControlStyleXXX`.
 *  @param completion Completion block
 */
- (void)setSlaveControlMode:(DJIRCControlMode)mode withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the Remote Controller's slave control mode.
 *
 */
- (void)getSlaveControlModeWithCompletion:(void (^)(DJIRCControlMode mode, NSError *_Nullable error))completion;

/**
 *  Called by the slave Remote Controller to set the gimbal's pitch, roll, and yaw speed with a range of [0, 100].
 *
 *  @param speed Gimal's pitch, roll, and yaw speed with a range of [0, 100].
 *  @param completion Completion block
 */
- (void)setSlaveJoystickControlGimbalSpeed:(DJIRCGimbalControlSpeed)speed withCompletion:(DJICompletionBlock)completion;

/**
 *  Gets the current slave's gimbal's pitch, roll, and yaw speed with a range of [0, 100].
 *
 */
- (void)getSlaveJoystickControlGimbalSpeedWithCompletion:(void (^)(DJIRCGimbalControlSpeed speed, NSError *_Nullable error))completion;


//-----------------------------------------------------------------
#pragma mark RC master and slave mode - Master RC methods
//-----------------------------------------------------------------

/**
 *  Used by the current master Remote Controller to get all the slaves connected to it.
 *
 *  @param block Remote execution result callback block. The arrray of slaves contains objects
 *  of type `DJIRCInfo`.
 */
- (void)getSlaveListWithCompletion:(void (^)(NSArray<DJIRCInfo *> *slaveList, NSError *_Nullable error))block;

/**
 *  Removes a slave Remote Controller from the current master Remote Controller.
 *
 *  @param slaveId Target slave to be removed.
 *  @param completion Completion block.
 */
- (void)removeSlave:(DJIRCID)slaveId withCompletion:(DJICompletionBlock)completion;

/**
 *  When a slave Remote Controller requests a master Remote Controller to control the gimbal, this
 *  method is used by a master Remote Controller to respond to the slave Remote Controller's request.
 *
 *  @param requesterId The slave Remote Controller's identifier.
 *  @param isAgree     YES if the master Remote Controller agrees to give the slave Remote Controller the right to control the gimbal.
 */
- (void)responseRequester:(DJIRCID)requesterId forGimbalControlRight:(BOOL)isAgree;

@end
NS_ASSUME_NONNULL_END
