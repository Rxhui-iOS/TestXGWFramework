//
//  RHtoCRHNaviManager.m
//  TZYJ_IPhone
//
//  Created by rxhui on 16/9/21.
//
//

#import "RHtoCRHNaviManager.h"
#import <RHXGWFramework/RHWebViewCotroller.h>
//#import "RHWebViewCotroller.h"
#import <CRHFramework/CRHMainViewController.h>
#import <RHXGWFramework/AccountTokenDataStore.h>
//#import "AccountTokenDataStore.h"

@implementation RHtoCRHNaviManager

+ (void)navigationToCRHControllerWithCurrent:(UIViewController *)currentController {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSString *userAgent = [[[UIWebView alloc] init] stringByEvaluatingJavaScriptFromString:@"navigator.userAgent"];
        
        NSRange range = [userAgent rangeOfString:@"crhsdk"];
        
        if (range.location == NSNotFound) {
            
            NSString *customUserAgent = [userAgent stringByAppendingFormat:@" %@",@"crhsdk"];
            [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"UserAgent":customUserAgent}];
        }
        
        CRHMainViewController* _mainViewController = [[CRHMainViewController alloc] init];
        
        _mainViewController.type=@"1"; //掌厅
        _mainViewController.channel = @"xgw";
        //        _mainViewController.appId = @"200";
        _mainViewController.identifier = @"com.crh.sjkh.chnl";
        _mainViewController.accessKey = @"com.crh.sjkh";
        //    _mainViewController.mobileNo = _TelePhone.text;
        //    _mainViewController.accessKey = @"3D0DB5B9D2FD642DE37FF42202EC531171A71FC898F8D0D5";
        //        _mainViewController.channel = @"999";
        //mainViewController.delegate = (id<MainViewDelegate>)self;
        NSTimeInterval time = [[NSDate date] timeIntervalSince1970];
        long long int date = (long long int)time;
        NSString *timeString = [NSString stringWithFormat:@"%lld", date];
        _mainViewController.agentSequenceId = timeString;
        
        /**
         * 颜色暂时注上，app里需要打开
         **/
//        _mainViewController.topViewColor = [UIColor colorWithRXHexString:@"0x07569f"];
        
        __block typeof(_mainViewController) blockMainViewController = _mainViewController;
        
        /**
         * 这段是跳转到智能小e的配置，如果有重复的类请删除
         **/
        _mainViewController.openExtraModuleBlock = ^(NSString *identify) {
            NSString * urlString = [NSString stringWithFormat:@"http://robot.rxhui.com/?hideTitle=0&userId=%@",[AccountTokenDataStore getAccountToken]];
            NSMutableDictionary * param = [NSMutableDictionary dictionary];
            [param setObject:urlString forKey:@"urlString"];
            [param setObject:@"智能问答机器人" forKey:@"title"];
            RHWebViewCotroller * webVc = [RHWebViewCotroller new];
            webVc.param = param;
            [blockMainViewController presentViewController:webVc animated:NO completion:nil];
        };
        
        //        [currentController.navigationController pushViewController:_mainViewController animated:YES];
        [currentController presentViewController:_mainViewController animated:NO completion:nil];
        
        
        //    [_mainViewController quitSjkh:^(CRHMainViewController *mainViewController) {
        //        [mainViewController dismissViewControllerAnimated:YES completion:nil];
        //    }];
        
        _mainViewController.mainViewBlock = ^(CRHMainViewController *mainViewController){
            
            [mainViewController dismissViewControllerAnimated:NO completion:nil];
//            [mainViewController.navigationController popViewControllerAnimated:YES];
        };
    });
}

@end
