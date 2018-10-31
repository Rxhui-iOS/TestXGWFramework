//
//  AppDelegate.m
//  TestXGWFramework
//
//  Created by 吴紫月 on 2018/1/18.
//  Copyright © 2018年 rxhui. All rights reserved.
//

#import "AppDelegate.h"

#import <RHXGWFramework/CMHttpURLManager.h>
#import <RHXGWFramework/STKAddress.h>
#import <RHXGWFramework/STKManager.h>
#import <RHXGWFramework/SKCodeTable.h>

#import <CRHFramework/AnyChatDefine.h>
#import <CRHFramework/AnyChatPlatform.h>

//#import <RHXGWFramework/AnyChatDefine.h>
//#import <RHXGWFramework/AnyChatPlatform.h>

#import "ViewController.h"

@interface AppDelegate ()



@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    //初始化AnyChatSDK
    [AnyChatPlatform InitSDK:0];
    
    //配置交易用的行情地址
    STKAddress *socketConfig = [[STKAddress alloc] initWithHost:@"phone.jinhui123.com" port:9002];
    [[STKManager defaultManager] configSocketWithAddress:socketConfig];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    //配置交易委托的地址
    NSString *hostPath = [[NSBundle mainBundle] pathForResource:@"config" ofType:@"xml"];
    NSString *suffixPath = [[NSBundle mainBundle] pathForResource:@"ServiceProvider" ofType:@"xml"];
    [CMHttpURLManager initConfigureWithHostPath:hostPath suffixPath:suffixPath];
    
    ViewController *mainViewController = [[ViewController alloc]init];
    
    UINavigationController *mainController = [[UINavigationController alloc]initWithRootViewController:mainViewController];
    self.window.rootViewController = mainController;
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    [[SKCodeTable instance] loadCodeTable];//读取本地股票代码
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_CORESDK_ACTIVESTATE :0];
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_CORESDK_ACTIVESTATE :0];
    [application beginBackgroundTaskWithExpirationHandler:^{
        
    }];
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_CORESDK_ACTIVESTATE :1];
    [AnyChatPlatform ActiveCallLog:YES];
    [application endBackgroundTask:UIBackgroundFetchResultNewData];
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
