//
//  ViewController.m
//  TestXGWFramework
//
//  Created by 吴紫月 on 2018/1/18.
//  Copyright © 2018年 rxhui. All rights reserved.
//

#import "ViewController.h"
#import <RHXGWFramework/TradeController.h>

#import "RHtoCRHNaviManager.h"

@interface ViewController ()

@property (nonatomic, strong) UIButton *tradeButton;

@property (nonatomic, strong) UIButton *buyButton;

@property (nonatomic, strong) TradeController *tradeController;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(navigationToCRHZT) name:@"kNaviToCRHZTNotification" object:nil];
    
    self.tradeButton = [[UIButton alloc]init];
    [self.tradeButton setTitle:@"交易" forState:UIControlStateNormal];
    [self.tradeButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
    [self.tradeButton addTarget:self action:@selector(navigationToTrade) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.tradeButton];
    
    self.buyButton = [[UIButton alloc]init];
    [self.buyButton setTitle:@"买入万科A" forState:UIControlStateNormal];
    [self.buyButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
    [self.buyButton addTarget:self action:@selector(navigationToBuy) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.buyButton];
    
    self.tradeController = [[TradeController alloc]init];
    //    tradeController.backButtonHidden = YES;//隐藏导航栏的返回按钮
    self.tradeController.isSecondTrade = YES;
    self.tradeController.navigationToStockDetailBlock = ^(NSDictionary *params) {
        NSLog(@"%@",params);
    };
}

- (void)navigationToCRHZT {
  
    [self.tradeController removeTradeLoginView];
    [RHtoCRHNaviManager navigationToCRHControllerWithCurrent:self.tradeController];
}

- (void)navigationToBuy {
    [self.navigationController pushViewController:self.tradeController animated:YES];
    [[NSNotificationCenter defaultCenter]postNotificationName:@"RHNavigationToTradeBuy" object:@"sz_000002"];
}

- (void)navigationToTrade {
    //发通知  参数 : @{@"channel":@"xgw",@"commission":@"0.025%"}  channel对应的是渠道号   commission 对应的是佣金
    //传参的
//     [[NSNotificationCenter defaultCenter] postNotificationName:@"Receiveparam" object:@{@"channel":@"xgw",@"commission":@"0.025%"}];
    
    //不传参数  或  不发此通知 默认commission为0.025% 没有渠道号
    [[NSNotificationCenter defaultCenter] postNotificationName:@"Receiveparam" object:nil];
    
    [self.navigationController pushViewController:self.tradeController animated:YES];
}

- (void)viewWillLayoutSubviews {
    self.tradeButton.frame = CGRectMake(100, 100, 100, 20);
    
    self.buyButton.frame = CGRectMake(100, 150, 100, 20);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
