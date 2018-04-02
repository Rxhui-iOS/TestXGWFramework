//
//  ViewController.m
//  TestXGWFramework
//
//  Created by 吴紫月 on 2018/1/18.
//  Copyright © 2018年 rxhui. All rights reserved.
//

#import "ViewController.h"
#import <RHXGWFramework/TradeController.h>

@interface ViewController ()

@property (nonatomic, strong) UIButton *tradeButton;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.tradeButton = [[UIButton alloc]init];
    [self.tradeButton setTitle:@"交易" forState:UIControlStateNormal];
    [self.tradeButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
    
    [self.tradeButton addTarget:self action:@selector(navigationToTrade) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview:self.tradeButton];
}

- (void)navigationToTrade {
    TradeController *tradeController = [[TradeController alloc]init];
//    tradeController.backButtonHidden = YES;//隐藏导航栏的返回按钮
    tradeController.isSecondTrade = YES;
    tradeController.navigationToStockDetailBlock = ^(NSDictionary *params) {
        NSLog(@"%@",params);
    };
    
    //发通知  参数 : @{@"channel":@"xgw",@"commission":@"0.025%"}  channel对应的是渠道号   commission 对应的是佣金
    //不传参数  或  不发此通知 默认channel为xgw  commission为0.025%
     [[NSNotificationCenter defaultCenter] postNotificationName:@"Receiveparam" object:@{@"channel":@"xgw",@"commission":@"0.025%"}];
    
    [self.navigationController pushViewController:tradeController animated:YES];
}

- (void)viewWillLayoutSubviews {
    self.tradeButton.frame = CGRectMake(100, 100, 100, 100);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
