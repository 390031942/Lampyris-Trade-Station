/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Base/Singleton.h>
#include <Model/TWS/TWSMessageDataDef.h>

// STD Include(s)
#include <set>
#include <unordered_map>
#include <functional>

// TWS Include(s)
#include <TWS/EWrapper.h>

class TWSEventDispatcherObject:public SingletonQObject<TWSEventDispatcherObject> {
	Q_OBJECT
Q_SIGNALS:
	/*
	 * 接收实时行情价格更新
	 * 参数{tickerId}: 行情ID，用于标识特定的市场数据请求
	 * 参数{field}: 行情类型，如最后成交价、买一价、卖一价等
	 * 参数{price}: 行情的价格
	 * 参数{attrib}: 行情属性，包含一些额外的行情信息
	 */
	void onResTickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib);

	/*
	 * 接收实时行情数量更新
	 * 参数{tickerId}: 行情ID，用于标识特定的市场数据请求
	 * 参数{field}: 行情类型，如最后成交量、买一量、卖一量等
	 * 参数{size}: 行情的数量
	 */
	void onResTickSize(TickerId tickerId, TickType field, Decimal size);

	/*
	 * 接收期权计算值更新
	 * 参数{tickerId}: 行情ID，用于标识特定的市场数据请求
	 * 参数{tickType}: 行情类型，特定于期权的行情类型
	 * 参数{tickAttrib}: 行情属性，期权特有的属性
	 * 参数{impliedVol}: 隐含波动率
	 * 参数{delta}: Delta值，期权价值对标的资产价格变动的敏感度
	 * 参数{optPrice}: 期权的理论价格
	 * 参数{pvDividend}: 现值股息
	 * 参数{gamma}: Gamma值，期权价值对标的资产价格变动的二阶导数
	 * 参数{vega}: Vega值，期权价值对波动率变动的敏感度
	 * 参数{theta}: Theta值，期权价值对时间流逝的敏感度
	 * 参数{undPrice}: 标的资产价格
	 */
	void onResTickOptionComputation(TickerId tickerId, TickType tickType, int tickAttrib, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);

	/*
	 * 接收字符串类型的行情更新
	 * 参数{tickerId}: 行情ID，用于标识特定的市场数据请求
	 * 参数{tickType}: 行情类型，用于指定接收的行情值类型
	 * 参数{value}: 行情的字符串值
	 */
	void onResTickString(TickerId tickerId, TickType tickType, const std::string& value);

	/*
	 * 接收EFP（Exchange for Physicals）行情更新
	 * 参数{tickerId}: 行情ID，用于标识特定的市场数据请求
	 * 参数{tickType}: 行情类型，特定于EFP的行情类型
	 * 参数{basisPoints}: 基点，表示EFP的溢价或折扣
	 * 参数{formattedBasisPoints}: 格式化后的基点字符串
	 * 参数{totalDividends}: 总股息
	 * 参数{holdDays}: 持有天数
	 * 参数{futureLastTradeDate}: 期货最后交易日
	 * 参数{dividendImpact}: 股息影响
	 * 参数{dividendsToLastTradeDate}: 至最后交易日的股息
	 */
	void onResTickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate);

	/*
	 * 接收订单状态更新
	 * 参数{orderId}: 订单ID，用于标识特定的订单
	 * 参数{status}: 订单当前的状态描述
	 * 参数{filled}: 已成交数量
	 * 参数{remaining}: 剩余未成交数量
	 * 参数{avgFillPrice}: 平均成交价格
	 * 参数{permId}: 永久订单ID，用于唯一标识一个订单
	 * 参数{parentId}: 父订单ID，用于标识订单的层级关系
	 * 参数{lastFillPrice}: 最后一笔成交价格
	 * 参数{clientId}: 客户ID，用于标识订单所属的客户
	 * 参数{whyHeld}: 订单被持有的原因
	 * 参数{mktCapPrice}: 市场资本化价格
	 */
	void onResOrderStatus(OrderId orderId, const std::string& status, Decimal filled, Decimal remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice);

	/*
	 * 接收通用行情值更新
	 * 参数{tickerId}: 行情ID，用于标识特定的市场数据请求
	 * 参数{tickType}: 行情类型，用于指定接收的行情值类型
	 * 参数{value}: 行情的值
	 */
	void onResTickGeneric(TickerId tickerId, TickType tickType, double value);

	/*
	 * 接收订单详细信息更新
	 * 参数{orderId}: 订单ID，用于标识特定的订单
	 * 参数{contract}: 合约信息，包含订单相关的合约详情
	 * 参数{order}: 订单信息，包含订单的类型、数量、价格等
	 * 参数{orderState}: 订单状态，包含订单的成交情况、剩余情况等
	 */
	void onResOpenOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState);

	/*
	 * 表示订单信息列表的结束
	 * 此函数在接收到所有订单信息后被调用，用于通知应用程序订单信息列表结束
	 */
	void onResOpenOrderEnd();

	/*
	 * 接收错误信息
	 * 参数{str}: 错误信息的描述
	 * 参数{lastError}: 最后一次错误代码
	 */
	void onResWinError(const std::string& str, int lastError);

	/*
	 * 连接关闭时调用
	 * 当与TWS的连接关闭时，此函数被调用，可以用于执行清理工作或重新连接逻辑
	 */
	void onResConnectionClosed();

	/*
	 * 接收账户值更新
	 * 参数{key}: 账户值的键名，标识账户的特定属性
	 * 参数{val}: 账户值的数值，对应键名的具体数值
	 * 参数{currency}: 账户值的货币单位
	 * 参数{accountName}: 账户名称，标识账户的所有者
	 */
	void onResUpdateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName);

	/*
	 * 接收投资组合更新
	 * 参数{contract}: 合约信息，包含投资组合中证券的详细信息
	 * 参数{position}: 投资组合中证券的持仓数量
	 * 参数{marketPrice}: 证券的市场价格
	 * 参数{marketValue}: 证券的市场价值，即市场价格乘以持仓数量
	 * 参数{averageCost}: 证券的平均成本价格
	 * 参数{unrealizedPNL}: 未实现盈亏，即当前市场价格与平均成本之间的差额
	 * 参数{realizedPNL}: 实现盈亏，即已卖出证券的盈亏
	 * 参数{accountName}: 账户名称，标识账户的所有者
	 */
	void onResUpdatePortfolio(const Contract& contract, Decimal position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName);

	/*
	 * 接收账户时间更新
	 * 参数{timeStamp}: 账户最后更新的时间戳
	 */
	void onResUpdateAccountTime(const std::string& timeStamp);

	/*
	 * 账户信息下载结束
	 * 当账户信息下载完成时调用此函数
	 * 参数{accountName}: 账户名称，标识账户的所有者
	 */
	void onResAccountDownloadEnd(const std::string& accountName);

	/*
	 * 下一个有效订单ID
	 * 当客户端需要创建新订单时，此函数返回下一个可用的订单ID
	 * 参数{orderId}: 下一个有效的订单ID
	 */
	void onResNextValidId(OrderId orderId);

	/*
	 * 接收合约详细信息
	 * 参数{reqId}: 请求ID，用于标识特定的请求
	 * 参数{contractDetails}: 合约详细信息，包含合约的各种属性
	 */
	void onResContractDetails(int reqId, const ContractDetails& contractDetails);

	/*
	 * 接收债券合约详细信息
	 * 参数{reqId}: 请求ID，用于标识特定的请求
	 * 参数{contractDetails}: 债券合约详细信息，包含债券合约的各种属性
	 */
	void onResBondContractDetails(int reqId, const ContractDetails& contractDetails);

	/*
	 * 合约详细信息列表结束
	 * 当接收到所有合约详细信息后调用此函数，表示列表结束
	 * 参数{reqId}: 请求ID，用于标识特定的请求
	 */
	void onResContractDetailsEnd(int reqId);

	/*
	 * 接收执行详情
	 * 参数{reqId}: 请求ID，用于标识特定的请求
	 * 参数{contract}: 合约信息，包含执行详情相关的合约详情
	 * 参数{execution}: 执行信息，包含订单的成交详情
	 */
	void onResExecDetails(int reqId, const Contract& contract, const Execution& execution);

	/*
	 * 执行详情列表结束
	 * 当接收到所有执行详情后调用此函数，表示列表结束
	 * 参数{reqId}: 请求ID，用于标识特定的请求
	 */
	void onResExecDetailsEnd(int reqId);

	/*
	 * 接收错误信息
	 * 参数{id}: 错误消息的ID，用于标识错误消息
	 * 参数{errorCode}: 错误代码，提供错误类型的数字表示
	 * 参数{errorString}: 错误信息的文本描述
	 * 参数{advancedOrderRejectJson}: 高级订单拒绝的JSON字符串，包含更多详细信息
	 */
	void onResError(int id, int errorCode, const std::string& errorString, const std::string& advancedOrderRejectJson);

	/*
	 * 接收市场深度更新
	 * 参数{id}: 行情ID，用于标识特定的市场数据请求
	 * 参数{position}: 市场深度的位置
	 * 参数{operation}: 操作类型，如添加、修改或删除市场深度项
	 * 参数{side}: 交易方向，买或卖
	 * 参数{price}: 价格
	 * 参数{size}: 订单簿的大小
	 */
	void onResUpdateMktDepth(TickerId id, int position, int operation, int side, double price, Decimal size);

	/*
	 * 接收Level 2市场深度更新
	 * 参数{id}: 行情ID，用于标识特定的市场数据请求
	 * 参数{position}: 市场深度的位置
	 * 参数{marketMaker}: 做市商的标识
	 * 参数{operation}: 操作类型，如添加、修改或删除市场深度项
	 * 参数{side}: 交易方向，买或卖
	 * 参数{price}: 价格
	 * 参数{size}: 订单簿的大小
	 * 参数{isSmartDepth}: 是否是智能市场深度
	 */
	void onResUpdateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation, int side, double price, Decimal size, bool isSmartDepth);

	/*
	 * 接收新闻公告更新
	 * 参数{msgId}: 消息ID，用于标识特定的新闻公告
	 * 参数{msgType}: 消息类型，如新闻、警告或完成
	 * 参数{newsMessage}: 新闻公告的消息内容
	 * 参数{originExch}: 新闻公告的来源交易所
	 */
	void onResUpdateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch);

	/*
	 * 接收受管理的账户列表
	 * 参数{accountsList}: 受管理的账户列表，以逗号分隔的字符串
	 */
	void onResManagedAccounts(const std::string& accountsList);

	/*
	 * 接收财务顾问数据
	 * 参数{pFaDataType}: 财务顾问数据类型
	 * 参数{cxml}: 财务顾问数据的CXML字符串
	 */
	void onResReceiveFA(faDataType pFaDataType, const std::string& cxml);

	/*
	 * 接收历史数据更新
	 * 参数{reqId}: 请求ID，用于标识特定的历史数据请求
	 * 参数{bar}: 包含历史数据的Bar对象
	 */
	void onResHistoricalData(TickerId reqId, const Bar& bar);

	/*
	 * 历史数据请求结束
	 * 当历史数据请求完成时调用此函数
	 * 参数{reqId}: 请求ID，用于标识特定的历史数据请求
	 * 参数{startDateStr}: 请求的历史数据的开始日期字符串
	 * 参数{endDateStr}: 请求的历史数据的结束日期字符串
	 */
	void onResHistoricalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr);

	/*
	 * 接收扫描仪参数
	 * 参数{xml}: 扫描仪参数的XML字符串
	 */
	void onResScannerParameters(const std::string& xml);

	/*
	 * 接收扫描仪数据更新
	 * 参数{reqId}: 请求ID，用于标识特定的扫描仪请求
	 * 参数{rank}: 扫描结果的排名
	 * 参数{contractDetails}: 合约详细信息，包含扫描结果中的合约详情
	 * 参数{distance}: 扫描条件的距离参数
	 * 参数{benchmark}: 基准参数
	 * 参数{projection}: 投影参数
	 * 参数{legsStr}: 期权链的字符串表示
	 */
	void onResScannerData(int reqId, int rank, const ContractDetails& contractDetails, const std::string& distance, const std::string& benchmark, const std::string& projection, const std::string& legsStr);

	/*
	 * 扫描仪数据请求结束
	 * 当扫描仪数据请求完成时调用此函数
	 * 参数{reqId}: 扫描仪请求ID
	 * 参数{contractList}: 扫描仪得到的合约列表
	 */
	void onResScannerDataEnd(int reqId, const std::vector<Contract>& contractList);

	/*
	 * 实时K线数据更新
	 * 参数{reqId}: 请求ID，用于标识特定的实时K线数据请求
	 * 参数{time}: K线的时间戳，通常是K线结束的时间
	 * 参数{open}: K线的开盘价
	 * 参数{high}: K线的最高价
	 * 参数{low}: K线的最低价
	 * 参数{close}: K线的收盘价
	 * 参数{volume}: K线的成交量
	 * 参数{wap}: K线的加权平均价格
	 * 参数{count}: K线期间的交易次数
	 */
	void onResRealtimeBar(TickerId reqId, long time, double open, double high, double low, double close, Decimal volume, Decimal wap, int count);

	/*
	 * 当前服务器时间更新
	 * 参数{time}: 服务器的当前时间戳
	 */
	void onResCurrentTime(long time);

	/*
	 * 基本面数据更新
	 * 参数{reqId}: 请求ID，用于标识特定的基本面数据请求
	 * 参数{data}: 基本面数据的字符串表示
	 */
	void onResFundamentalData(TickerId reqId, const std::string& data);

	/*
	 * Delta中性验证信息更新
	 * 参数{reqId}: 请求ID，用于标识特定的Delta中性验证请求
	 * 参数{deltaNeutralContract}: Delta中性合约信息，包含合约和Delta/价格的组合
	 */
	void onResDeltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract);

	/*
	 * 市场快照数据结束
	 * 当市场快照数据请求完成时调用此函数
	 * 参数{reqId}: 请求ID，用于标识特定的市场快照请求
	 */
	void onResTickSnapshotEnd(int reqId);

	/*
	 * 市场数据类型更新
	 * 参数{reqId}: 请求ID，用于标识特定的市场数据类型请求
	 * 参数{marketDataType}: 当前的市场数据类型，如实时、延时等
	 */
	void onResMarketDataType(TickerId reqId, int marketDataType);

	/*
	 * 佣金报告更新
	 * 参数{commissionReport}: 佣金报告对象，包含交易的佣金详情
	 */
	void onResCommissionReport(const CommissionReport& commissionReport);

	/*
	 * 持仓更新
	 * 参数{account}: 账户名称，标识账户的所有者
	 * 参数{contract}: 合约对象，包含持仓相关的合约详情
	 * 参数{position}: 持仓数量
	 * 参数{avgCost}: 平均成本价格
	 */
	void onResPosition(const std::string& account, const Contract& contract, Decimal position, double avgCost);

	/*
	 * 持仓列表结束
	 * 当接收到所有持仓信息后调用此函数，表示持仓列表结束
	 */
	void onResPositionEnd(const std::vector<PositionData>& position);

	/*
	 * 账户摘要更新
	 * 参数{reqId}: 请求ID，用于标识特定的账户摘要请求
	 * 参数{account}: 账户名称，标识账户的所有者
	 * 参数{tag}: 摘要标签，标识摘要的特定属性
	 * 参数{value}: 摘要值，对应标签的具体数值
	 * 参数{curency}: 摘要值的货币单位
	 */
	void onResAccountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& currency);

	/*
	 * 账户摘要请求结束
	 * 当账户摘要请求完成时调用此函数
	 * 参数{reqId}: 请求ID，用于标识特定的账户摘要请求
	 */
	void onResAccountSummaryEnd(int reqId);

	/*
	 * API消息验证响应
	 * 参数{apiData}: 从API接收到的数据
	 */
	void onResVerifyMessageAPI(const std::string& apiData);

	/*
	 * 验证完成事件
	 * 参数{isSuccessful}: 验证是否成功
	 * 参数{errorText}: 如果验证失败，提供错误信息的文本
	 */
	void onResVerifyCompleted(bool isSuccessful, const std::string& errorText);

	/*
	 * 显示分组列表响应
	 * 参数{reqId}: 请求ID，用于标识特定的显示分组请求
	 * 参数{groups}: 分组列表，以字符串形式返回
	 */
	void onResDisplayGroupList(int reqId, const std::string& groups);

	/*
	 * 显示分组更新事件
	 * 参数{reqId}: 请求ID，用于标识特定的显示分组更新请求
	 * 参数{contractInfo}: 合约信息的更新
	 */
	void onResDisplayGroupUpdated(int reqId, const std::string& contractInfo);

	/*
	 * API消息验证和授权响应
	 * 参数{apiData}: 从API接收到的数据
	 * 参数{xyzChallange}: 授权挑战字符串
	 */
	void onResVerifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange);

	/*
	 * 验证和授权完成事件
	 * 参数{isSuccessful}: 验证和授权是否成功
	 * 参数{errorText}: 如果验证和授权失败，提供错误信息的文本
	 */
	void onResVerifyAndAuthCompleted(bool isSuccessful, const std::string& errorText);

	/*
	 * 连接确认事件
	 * 此函数在客户端与TWS服务器建立连接时调用
	 */
	void onResConnectAck();

	/*
	 * 多账户持仓更新
	 * 参数{reqId}: 请求ID，用于标识特定的多账户持仓请求
	 * 参数{account}: 账户名称
	 * 参数{modelCode}: 模型代码
	 * 参数{contract}: 合约对象，包含持仓相关的合约详情
	 * 参数{pos}: 持仓数量
	 * 参数{avgCost}: 平均成本价格
	 */
	void onResPositionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, Decimal pos, double avgCost);

	/*
	 * 多账户持仓列表结束
	 * 当接收到所有多账户持仓信息后调用此函数，表示持仓列表结束
	 * 参数{reqId}: 请求ID，用于标识特定的多账户持仓请求
	 */
	void onResPositionMultiEnd(int reqId);

	/*
	 * 多账户更新
	 * 参数{reqId}: 请求ID，用于标识特定的多账户更新请求
	 * 参数{account}: 账户名称
	 * 参数{modelCode}: 模型代码
	 * 参数{key}: 账户属性的键
	 * 参数{value}: 账户属性的值
	 * 参数{currency}: 账户属性值的货币单位
	 */
	void onResAccountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency);

	/*
	 * 多账户更新列表结束
	 * 当接收到所有多账户更新信息后调用此函数，表示更新列表结束
	 * 参数{reqId}: 请求ID，用于标识特定的多账户更新请求
	 */
	void onResAccountUpdateMultiEnd(int reqId);

	/*
	 * 期权合约参数定义响应
	 * 参数{reqId}: 请求ID，用于标识特定的期权合约参数请求
	 * 参数{exchange}: 交易所代码
	 * 参数{underlyingConId}: 标的合约ID
	 * 参数{tradingClass}: 交易类别
	 * 参数{multiplier}: 合约乘数
	 * 参数{expirations}: 期权合约的到期日集合
	 * 参数{strikes}: 期权合约的执行价格集合
	 */
	void onResSecurityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes);

	/*
	 * 期权合约参数定义结束
	 * 参数{reqId}: 请求ID，用于标识特定的期权合约参数请求结束
	 */
	void onResSecurityDefinitionOptionalParameterEnd(int reqId);

	/*
	 * 软美元等级信息响应
	 * 参数{reqId}: 请求ID，用于标识特定的软美元等级请求
	 * 参数{tiers}: 软美元等级列表
	 */
	void onResSoftDollarTiers(int reqId, const std::vector<SoftDollarTier>& tiers);

	/*
	 * 家族代码列表响应
	 * 参数{familyCodes}: 家族代码列表
	 */
	void onResFamilyCodes(const std::vector<FamilyCode>& familyCodes);

	/*
	 * 合约样本列表响应
	 * 参数{reqId}: 请求ID，用于标识特定的合约样本请求
	 * 参数{contractDescriptions}: 合约描述列表
	 */
	void onResSymbolSamples(int reqId, const std::vector<ContractDescription>& contractDescriptions);

	/*
	 * 市场深度交易所列表响应
	 * 参数{depthMktDataDescriptions}: 市场深度数据描述列表
	 */
	void onResMktDepthExchanges(const std::vector<DepthMktDataDescription>& depthMktDataDescriptions);

	/*
	 * 行情新闻响应
	 * 参数{tickerId}: 行情ID
	 * 参数{timeStamp}: 新闻时间戳
	 * 参数{providerCode}: 新闻提供者代码
	 * 参数{articleId}: 文章ID
	 * 参数{headline}: 头条新闻
	 * 参数{extraData}: 额外数据
	 */
	void onResTickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData);

	/*
	 * 智能组件响应
	 * 参数{reqId}: 请求ID，用于标识特定的智能组件请求
	 * 参数{theMap}: 智能组件映射
	 */
	void onResSmartComponents(int reqId, const SmartComponentsMap& theMap);

	/*
	 * 行情请求参数响应
	 * 参数{tickerId}: 行情ID
	 * 参数{minTick}: 最小价格变动单位
	 * 参数{bboExchange}: 最佳出价和要价的交易所代码
	 * 参数{snapshotPermissions}: 快照权限
	 */
	void onResTickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions);

	/*
	 * 新闻提供者列表响应
	 * 参数{newsProviders}: 新闻提供者列表
	 */
	void onResNewsProviders(const std::vector<NewsProvider>& newsProviders);

	/*
	 * 新闻文章响应
	 * 参数{requestId}: 请求ID，用于标识特定的新闻文章请求
	 * 参数{articleType}: 文章类型
	 * 参数{articleText}: 文章文本
	 */
	void onResNewsArticle(int requestId, int articleType, const std::string& articleText);

	/*
	 * 历史新闻数据响应
	 * 参数{requestId}: 请求ID，用于标识特定的历史新闻数据请求
	 * 参数{time}: 新闻发生的时间
	 * 参数{providerCode}: 新闻提供者的代码
	 * 参数{articleId}: 文章的唯一标识符
	 * 参数{headline}: 新闻的标题
	 */
	void onResHistoricalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline);

	/*
	 * 历史新闻数据结束
	 * 参数{requestId}: 请求ID，用于标识特定的历史新闻数据请求
	 * 参数{hasMore}: 指示是否还有更多的历史新闻数据
	 */
	void onResHistoricalNewsEnd(int requestId, bool hasMore);

	/*
	 * 市场深度数据的时间戳响应
	 * 参数{reqId}: 请求ID，用于标识特定的市场深度数据请求
	 * 参数{headTimestamp}: 市场深度数据的时间戳
	 */
	void onResHeadTimestamp(int reqId, const std::string& headTimestamp);

	/*
	 * 直方图数据响应
	 * 参数{reqId}: 请求ID，用于标识特定的直方图数据请求
	 * 参数{data}: 直方图数据向量
	 */
	void onResHistogramData(int reqId, const HistogramDataVector& data);

	/*
	 * 历史数据更新
	 * 参数{reqId}: 请求ID，用于标识特定的历史数据请求
	 * 参数{bar}: 包含历史数据的Bar对象
	 */
	void onResHistoricalDataUpdate(TickerId reqId, const Bar& bar);

	/*
	 * 市场数据请求重定向
	 * 参数{reqId}: 请求ID，用于标识特定的市场数据请求
	 * 参数{conid}: 合约ID
	 * 参数{exchange}: 交易所代码
	 */
	void onResRerouteMktDataReq(int reqId, int conid, const std::string& exchange);

	/*
	 * 市场深度请求重定向
	 * 参数{reqId}: 请求ID，用于标识特定的市场深度请求
	 * 参数{conid}: 合约ID
	 * 参数{exchange}: 交易所代码
	 */
	void onResRerouteMktDepthReq(int reqId, int conid, const std::string& exchange);

	/*
	 * 市场规则响应
	 * 参数{marketRuleId}: 市场规则ID
	 * 参数{priceIncrements}: 价格增量向量，包含不同价格水平的价格步长
	 */
	void onResMarketRule(int marketRuleId, const std::vector<PriceIncrement>& priceIncrements);

	/*
	 * 盈亏响应
	 * 参数{reqId}: 请求ID，用于标识特定的盈亏请求
	 * 参数{dailyPnL}: 日盈亏
	 * 参数{unrealizedPnL}: 未实现盈亏
	 * 参数{realizedPnL}: 实现盈亏
	 */
	void onResPnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL);

	/*
	 * 单一持仓盈亏响应
	 * 参数{reqId}: 请求ID，用于标识特定的单一持仓盈亏请求
	 * 参数{pos}: 持仓数量
	 * 参数{dailyPnL}: 日盈亏
	 * 参数{unrealizedPnL}: 未实现盈亏
	 * 参数{realizedPnL}: 实现盈亏
	 * 参数{value}: 持仓的总价值
	 */
	void onResPnlSingle(int reqId, Decimal pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value);

	/*
	 * 历史成交价格响应
	 * 参数{reqId}: 请求ID，用于标识特定的历史成交价格请求
	 * 参数{ticks}: 成交价格的向量
	 * 参数{done}: 指示是否完成了所有历史数据的发送
	 */
	void onResHistoricalTicks(int reqId, const std::vector<HistoricalTick>& ticks, bool done);

	/*
	 * 历史买卖报价响应
	 * 参数{reqId}: 请求ID，用于标识特定的历史买卖报价请求
	 * 参数{ticks}: 买卖报价的向量
	 * 参数{done}: 指示是否完成了所有历史数据的发送
	 */
	void onResHistoricalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done);

	/*
	 * 历史最后成交价格响应
	 * 参数{reqId}: 请求ID，用于标识特定的历史最后成交价格请求
	 * 参数{ticks}: 最后成交价格的向量
	 * 参数{done}: 指示是否完成了所有历史数据的发送
	 */
	void onResHistoricalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done);

	/*
	 * 逐笔成交数据响应
	 * 参数{reqId}: 请求ID，用于标识特定的逐笔成交数据请求
	 * 参数{tickType}: 成交类型
	 * 参数{time}: 成交时间的时间戳
	 * 参数{price}: 成交价格
	 * 参数{size}: 成交数量
	 * 参数{tickAttribLast}: 成交属性
	 * 参数{exchange}: 成交的交易所
	 * 参数{specialConditions}: 特殊条件
	 */
	void onResTickByTickAllLast(int reqId, int tickType, time_t time, double price, Decimal size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions);

	/*
	 * 逐笔买卖报价数据响应
	 * 参数{reqId}: 请求ID，用于标识特定的逐笔买卖报价数据请求
	 * 参数{time}: 报价时间的时间戳
	 * 参数{bidPrice}: 买价
	 * 参数{askPrice}: 卖价
	 * 参数{bidSize}: 买量
	 * 参数{askSize}: 卖量
	 * 参数{tickAttribBidAsk}: 买卖报价属性
	 */
	void onResTickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, Decimal bidSize, Decimal askSize, const TickAttribBidAsk& tickAttribBidAsk);

	/*
	 * 逐笔中间价数据响应
	 * 参数{reqId}: 请求ID，用于标识特定的逐笔中间价数据请求
	 * 参数{time}: 中间价时间的时间戳
	 * 参数{midPoint}: 中间价
	 */
	void onResTickByTickMidPoint(int reqId, time_t time, double midPoint);

	/*
	 * 订单绑定响应
	 * 参数{orderId}: 订单ID
	 * 参数{apiClientId}: API客户端ID
	 * 参数{apiOrderId}: API订单ID
	 */
	void onResOrderBound(long long orderId, int apiClientId, int apiOrderId);

	/*
	 * 完成的订单响应
	 * 参数{contract}: 合约对象
	 * 参数{order}: 订单对象
	 * 参数{orderState}: 订单状态对象
	 */
	void onResCompletedOrder(const Contract& contract, const Order& order, const OrderState& orderState);

	/*
	 * 完成的订单列表结束
	 * 此函数在所有完成的订单数据发送完毕后调用
	 */
	void onResCompletedOrdersEnd();

	/*
	 * 替换FA账户结束响应
	 * 参数{reqId}: 请求ID，用于标识特定的FA账户替换请求
	 * 参数{text}: 替换操作的文本描述
	 */
	void onResReplaceFAEnd(int reqId, const std::string& text);

	/*
	 * 工作站元数据响应
	 * 参数{reqId}: 请求ID，用于标识特定的工作站元数据请求
	 * 参数{dataJson}: 元数据的JSON字符串
	 */
	void onResWshMetaData(int reqId, const std::string& dataJson);

	/*
	 * 工作站事件数据响应
	 * 参数{reqId}: 请求ID，用于标识特定的工作站事件数据请求
	 * 参数{dataJson}: 事件数据的JSON字符串
	 */
	void onResWshEventData(int reqId, const std::string& dataJson);

	/*
	 * 历史交易时间表响应
	 * 参数{reqId}: 请求ID，用于标识特定的历史交易时间表请求
	 * 参数{startDateTime}: 开始日期和时间
	 * 参数{endDateTime}: 结束日期和时间
	 * 参数{timeZone}: 时区
	 * 参数{sessions}: 交易会话的向量
	 */
	void onResHistoricalSchedule(int reqId, const std::string& startDateTime, const std::string& endDateTime, const std::string& timeZone, const std::vector<HistoricalSession>& sessions);

	/*
	 * 用户信息响应
	 * 参数{reqId}: 请求ID，用于标识特定的用户信息请求
	 * 参数{whiteBrandingId}: 白标ID，用于识别用户
	 */
	void onResUserInfo(int reqId, const std::string& whiteBrandingId);
};

#ifndef TWSEventDispatcherObject
 #define TWSEventDispatcher TWSEventDispatcherObject::getInstance()
 #define TWSEventBind(eventName,func) \
	 QObject::connect(TWSEventDispatcher,&eventName,TWSEventDispatcher,std::move(func),Qt::ConnectionType::QueuedConnection);
 #define TWSEventUnbind(eventName,func) \
	 QObject::disconnect(TWSEventDispatcher,&eventName,func);
 #define TWSEventType TWSEventDispatcherObject
#endif // !EventDispatcher
