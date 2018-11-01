//
//  CRHMainViewController.h
//  crh-sjkh
//
//  Created by milo on 14-3-24.
//  Copyright (c) 2014年 com.cairh. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "VideoChatController.h"
#import "CertFileUtil.h"
#import <sys/utsname.h>
#import "MBProgressHUD_CRH.h"
#import <CoreLocation/CoreLocation.h>
#import "ImageCropViewController.h"
#import "CameraOverlayView.h"
#import "CRHUIImagePickerViewController.h"
#if DBZQYM
    #import "YMCRHObj.h"
#endif

#if EXOCR

#import <ExCardSDK/ExCardSDK.h>
#import <ExBankCardSDK/ExBankCardSDK.h>

#endif


#if ! __has_feature(objc_arc)
#warning This file must be compiled with ARC. Use -fobjc-arc flag (or convert project to ARC).
#endif
//获取设备的物理高度
#define SCHEIGHT [UIScreen mainScreen].bounds.size.height
//获取设备的物理宽度
#define SCWIDTH [UIScreen mainScreen].bounds.size.width
//获取当前设备版本号
#define IOS_SYS_VERSION [[[UIDevice currentDevice] systemVersion] floatValue]
//定义颜色RGB
#define RGBCOLOR(r, g, b)       [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:1]
#define RGBACOLOR(r, g, b, a)   [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:(a)]
//16进制颜色RGB
#define UIColorFromRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]
/**
 * 取注册手机号
 */
#define FUNC_NO_GET_MOBILE_NO 1001
/**
 * 取设备平台版本、型号
 */
#define FUNC_NO_GET_DEVICE_MODEL 1002
/**
 * 取设备唯一标示
 */
#define FUNC_NO_GET_DEVICE_ID 1004

#define FUNC_NO_GET_CHANNEL_INFO  1003



@class CRHMainViewController;

@protocol CRHMainViewDelegate <NSObject>

-(void) quitSjkh  DEPRECATED_ATTRIBUTE;

@end
typedef void (^CRHMainViewBlock)(CRHMainViewController *mainViewController);
typedef void (^ReturnAppBlock)(CRHMainViewController *mainViewcontroller);
typedef void (^OpenExtraModuleBlock)(NSString *identifier);
typedef void (^CRHLogin)();
typedef void (^CRHLoginOut)();
typedef void (^CRHLoginOutTime)();
typedef void (^CRHbankCardManagementBlock)();

typedef void (^CRHOtherLogout)(NSString *logOutType);
//财富需求
//typedef void (^QuitStatuseBlock)(NSInteger errorNo,NSString *errorInfo);

/**
 * @param Class CRHReSource
 * 处理MainViewController的资源及一些其他函数
 *
 */

@interface CRHReSourece : NSObject
{
    
    
    
}
@property(nonatomic,copy) NSString *username;
@property(nonatomic,copy) NSString *passWord;

+(CRHReSourece *)sharedStore;

@end


@interface CRHMainViewController : UIViewController<AnyChatNotifyMessageDelegate,AnyChatTextMsgDelegate,AnyChatTransDataDelegate,UIWebViewDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate,VideoChatControllerDelegate,NSURLConnectionDelegate,MBProgressHUDDelegate_CRH,CLLocationManagerDelegate,ImageCropViewControllerDelegate>
{
    @package
    VideoChatController* videoChatController;
    AnyChatPlatform *anychat;   //Anycaht核心
    int iCurrentChatUserId;     //本地视频用户ID
    int iRemoteUserId;          //远端视频用户ID
    NSString *videoServerIp;    //视频服务地址
    int videoServerPort;        //视频服务端口
    int videoRoomId;            //视频房间号
    
    NSString *mPicType;
    NSString *bizStr;
    NSString *mCookieStr;
    NSString *cameraType;
    
    NSString *appGuid;
    
    //下拉菜单
    UIActionSheet *myActionSheet;
    //网络异常提示框
    UIAlertView *showLoadFail;
    
    NSString* webServerUrl;
    NSString* uploadPicUrl;
    NSString* uploadVideoUrl;
    NSString* videoMsg;
    NSString* uploadLogUrl;
    NSString* currVersion;
    NSString *cookieDomain;
    NSString *cookiePath;
    BOOL rifImg;
    NSString* userId;
    NSString* userName;
    CGRect viewCGRect;
    
    NSString *videoURL;
    //https
    NSURL *_currenURL;
    NSURLConnection* reUrlConnection;//重发请求
    NSURLRequest* originRequest;
   
    double longitudeValue ;
    double latitudeValue;
    NSString* province;
    NSString* city;
    CRHUIImagePickerViewController * imagePickerCamera;
    CRHUIImagePickerViewController * imagePickerPhoto;
    UIImagePickerController * imagePicker;
    CameraOverlayView * cameraOverlayView;
    
    int memorySize;//内存大小,小于512m为1,大于512m为2
    BOOL hideLogo;
    
    NSString *_jsonStr;
    NSString *copy2ClipboardStr;
    
    BOOL _isZt;
    NSString *backZt;
    
    //方正大头照标题
    NSString *bigHeadPhoto;
    
#if DBZQYM
    YMCRHObj *appDlg;
    NSInteger exCardIndex;
#endif
    
}


@property(nonatomic,assign) BOOL isLoadHttpServerXml;//默认为NO传yes加载网络配置文件


//特殊业务参数
/*
 传入json字符串比如:
 {
 "indexUrl": "http://sjkhtest.tpyzq.com/indexnew?befromFlag=other",
 "uploadPicUrl": "http://sjkhtest.tpyzq.com/upload",
 "cookieDomain": "sjkhtest.tpyzq.com"
 }
 */
@property(nonatomic,copy) NSString *configUrlJsonStr;
@property(nonatomic,copy) NSString *channel1;
@property(nonatomic,copy) NSString *clientChannel;

@property(nonatomic,assign) BOOL isOpenLocation;

//易道博识
#if EXOCR
@property (nonatomic, strong) EXOCRIDCardInfo * IDInfo;
@property (nonatomic, strong) EXOCRBankCardInfo *BANKInfo;
#endif

//加载网络配置传递的一些参数
@property(nonatomic,copy) NSString *sjkhConfigName;//下载网络配置文件默认为servers.xml
@property(nonatomic,copy) NSString *configUrl; //下载网络配置文件的地址
@property(nonatomic,copy) NSString *clientId;
@property(nonatomic,copy) NSString *versionChannel;
@property(nonatomic,copy) NSString *ext;
@property(nonatomic,copy) NSString *sourceNo;


@property (nonatomic,weak) id<CRHMainViewDelegate> delegate;
@property (nonatomic,strong) UIWebView* myWebView;
@property (nonatomic,strong) UIImageView* imgView;
@property (nonatomic,strong) VideoChatController* videoChatController;


 //注册手机号，第三方嵌入时如果要传入手机号 用此方法（手机号已经在第三方客户端获取）
@property (nonatomic,copy) NSString* mobileNo;
@property (nonatomic,copy) NSString* channel;
@property (nonatomic,copy) NSString* accessKey;
@property (nonatomic,copy) NSString* appId;
@property (nonatomic,copy) NSString* type;

@property (nonatomic,copy) NSString *username;
@property (nonatomic,copy) NSString *password;
//加载思迪掌厅的参数密文
@property (nonatomic,copy) NSString *paramCiphertext;

//使用usertoken、mobilecode登录
@property (nonatomic,copy) NSString *user_token;
@property (nonatomic,copy) NSString *mobilecode;

//委托方式
@property (nonatomic,copy) NSString  *entrustment;
//跳转模块
@property (nonatomic,copy) NSString *ztModule;
@property (nonatomic,copy) NSString *loginFlag;//1登录状态，0非登录状态


@property (nonatomic,copy) NSString *loginToken;
@property (nonatomic,copy) NSString* prodCode;
@property (nonatomic,copy) NSString *prodName;
@property (nonatomic,copy) NSString* accountType;
@property (nonatomic,strong) UIColor *topViewColor;
@property (nonatomic,copy) NSString *identifier;
@property (nonatomic,copy) CRHMainViewBlock mainViewBlock;

@property (nonatomic,copy) NSString *agentSequenceId;
//太平洋sdk对接
@property (nonatomic,copy) NSString *lcs_uid;
@property (nonatomic,copy) ReturnAppBlock returnAppBlock;
//quit status
@property (nonatomic,copy) OpenExtraModuleBlock openExtraModuleBlock;
@property (nonatomic,copy) CRHOtherLogout crhOtherLogout;
@property (nonatomic,copy) NSString *callOtherLoginFuc;
@property (nonatomic,assign) NSInteger quitErrorNo;
@property (nonatomic,copy) NSString *quitErrorInfo;
@property (nonatomic,copy) CRHLogin loginBlock;
@property (nonatomic,assign,getter =isAuthed)BOOL authed;
@property (nonatomic,strong)NSURL *currenURL;
@property (nonatomic,strong) CLLocationManager *locationManager;

//掌厅自定接口
//@property(nonatomic,strong) CRHLogin crhLogin;
@property(nonatomic,copy) CRHLoginOut crhLoginOut;
@property(nonatomic,copy) CRHLoginOutTime crhLoginOutTime;
@property(nonatomic,copy) CRHbankCardManagementBlock crhBankCardManageMentBlock;

//财富需求
//@property(nonatomic,strong)QuitStatuseBlock quitStatuseblock;

//tabBarheight为tabBar的高度系统一般为49,sdk默认为0
@property(nonatomic,assign) CGFloat tabBarHeight;


//自定接口
@property (nonatomic,strong) NSString *token;
@property (nonatomic,strong) NSString *podid;

#if DBZQYM
@property(nonatomic, copy) NSString *chViewNumberStr;
#endif


-(void)requstSuccess:(NSString*)result;
-(void)requstFail:(NSString*)err;
-(void)callHtmlJS:(NSString*)js;
-(NSString *)picType;
-(NSString *)cookieStr;
-(void)quitViewController;
-(void)clearCookieCache;
-(void)startCamera:(UIImagePickerControllerSourceType)sourceType;
-(void)openMenu;
-(void)takePictures:(NSString *) picType : (NSString *) cookieStr;
-(void)takePictures2:(NSString *)picType : (NSString *) cookieStr;
-(void)readPlisturl:(NSString *)tabId;
-(void)loadHtml: (UIWebView *)webView_;
-(void)crhLoginView;
-(void)initAnychatSDK;
-(void)loginOut;
-(void)takeBankVideo:(NSString *)callFunction;

-(NSString *)getDeviceId:(NSString *) callback;
-(NSString *)getNetWorkType:(NSString *) callUrl;
-(NSString *)dictionaryToJson:(NSDictionary *)dic;
//退出时候回调该函数
-(void)quitSjkh:(CRHMainViewBlock)blockInfo;
//财富退出时候返回状态
//-(void)quitStatuse:(QuitStatuseBlock)quitBlock;
-(void)returnApp:(ReturnAppBlock)block;
//调起集成方登录框
-(void)callLoginView:(CRHLogin)block;
-(void)loginSuccess:(NSString *)loginUsername passWord:(NSString *)loginPassWord;
-(void)tokenLoginSuccess:(NSString *)userToken mobileCode:(NSString *)mobileCode;
//block回调参数loginOutType如果是1，为重置密码推出，如果是其它或者是空字符串为普通推出
-(void)callOtherLoginOut:(CRHOtherLogout) otherLogOut;

//调起第三方即答系统接口
-(void)openExtraModuleBlock:(OpenExtraModuleBlock)block;
-(void)copyCliport:(id)sender;
-(void)takeIdCard:(NSString *)cameroType selectPicType:(NSString *)selectType callBack:(NSString *)cameroCallBack;
-(void)crhCallOtherLogOut:(NSString *)logType;
//修改状态栏遮罩
-(void)updateStatusBarColor:(NSString *)crhColorStr;
-(void)callCRHKeyBord:(NSDictionary *)keyBordDictionary;



//掌厅自定义修改接口
//调用商城登录
-(void)loginTrade:(CRHLogin)login;
//退出登录
-(void)loginOutTrade:(CRHLoginOut)loginOut;
//验证token
-(void)tokenLogin:(NSString *)token Account:(NSString *)account;
//跳入商城选择页面
- (void)selectViewController:(NSString *)prodID;
//弹出银行卡页面
- (void)getbankCardManagement:(CRHbankCardManagementBlock)crhBankCardBlock;
//超时刷新登录状态
-(void)crhLoginOutTimeAction:(CRHLoginOutTime)loginOut;
-(void)logOut;
//加载更多
-(void)loadProductsList;
//进入赎回页面
-(void)goProdPage:(NSString *)prodcode;


#if EXOCR
//调用易道博识识别系统
-(void)openexORC:(NSString *)picturetype callBack:(NSString *)callBackFuc scanTime:(NSString *)exocrScanTime;
//银行卡识别
-(void)scanBank:(NSString *)callFunction scanType:(NSString *)scanType name:(NSString *)bankCardName scanTime:(NSString *)exocrScanTime;
#endif

@end