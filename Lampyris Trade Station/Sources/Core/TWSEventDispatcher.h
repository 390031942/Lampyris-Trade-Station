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
	 * ����ʵʱ����۸����
	 * ����{tickerId}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{field}: �������ͣ������ɽ��ۡ���һ�ۡ���һ�۵�
	 * ����{price}: ����ļ۸�
	 * ����{attrib}: �������ԣ�����һЩ�����������Ϣ
	 */
	void onResTickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib);

	/*
	 * ����ʵʱ������������
	 * ����{tickerId}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{field}: �������ͣ������ɽ�������һ������һ����
	 * ����{size}: ���������
	 */
	void onResTickSize(TickerId tickerId, TickType field, Decimal size);

	/*
	 * ������Ȩ����ֵ����
	 * ����{tickerId}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{tickType}: �������ͣ��ض�����Ȩ����������
	 * ����{tickAttrib}: �������ԣ���Ȩ���е�����
	 * ����{impliedVol}: ����������
	 * ����{delta}: Deltaֵ����Ȩ��ֵ�Ա���ʲ��۸�䶯�����ж�
	 * ����{optPrice}: ��Ȩ�����ۼ۸�
	 * ����{pvDividend}: ��ֵ��Ϣ
	 * ����{gamma}: Gammaֵ����Ȩ��ֵ�Ա���ʲ��۸�䶯�Ķ��׵���
	 * ����{vega}: Vegaֵ����Ȩ��ֵ�Բ����ʱ䶯�����ж�
	 * ����{theta}: Thetaֵ����Ȩ��ֵ��ʱ�����ŵ����ж�
	 * ����{undPrice}: ����ʲ��۸�
	 */
	void onResTickOptionComputation(TickerId tickerId, TickType tickType, int tickAttrib, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);

	/*
	 * �����ַ������͵��������
	 * ����{tickerId}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{tickType}: �������ͣ�����ָ�����յ�����ֵ����
	 * ����{value}: ������ַ���ֵ
	 */
	void onResTickString(TickerId tickerId, TickType tickType, const std::string& value);

	/*
	 * ����EFP��Exchange for Physicals���������
	 * ����{tickerId}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{tickType}: �������ͣ��ض���EFP����������
	 * ����{basisPoints}: ���㣬��ʾEFP����ۻ��ۿ�
	 * ����{formattedBasisPoints}: ��ʽ����Ļ����ַ���
	 * ����{totalDividends}: �ܹ�Ϣ
	 * ����{holdDays}: ��������
	 * ����{futureLastTradeDate}: �ڻ��������
	 * ����{dividendImpact}: ��ϢӰ��
	 * ����{dividendsToLastTradeDate}: ��������յĹ�Ϣ
	 */
	void onResTickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate);

	/*
	 * ���ն���״̬����
	 * ����{orderId}: ����ID�����ڱ�ʶ�ض��Ķ���
	 * ����{status}: ������ǰ��״̬����
	 * ����{filled}: �ѳɽ�����
	 * ����{remaining}: ʣ��δ�ɽ�����
	 * ����{avgFillPrice}: ƽ���ɽ��۸�
	 * ����{permId}: ���ö���ID������Ψһ��ʶһ������
	 * ����{parentId}: ������ID�����ڱ�ʶ�����Ĳ㼶��ϵ
	 * ����{lastFillPrice}: ���һ�ʳɽ��۸�
	 * ����{clientId}: �ͻ�ID�����ڱ�ʶ���������Ŀͻ�
	 * ����{whyHeld}: ���������е�ԭ��
	 * ����{mktCapPrice}: �г��ʱ����۸�
	 */
	void onResOrderStatus(OrderId orderId, const std::string& status, Decimal filled, Decimal remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice);

	/*
	 * ����ͨ������ֵ����
	 * ����{tickerId}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{tickType}: �������ͣ�����ָ�����յ�����ֵ����
	 * ����{value}: �����ֵ
	 */
	void onResTickGeneric(TickerId tickerId, TickType tickType, double value);

	/*
	 * ���ն�����ϸ��Ϣ����
	 * ����{orderId}: ����ID�����ڱ�ʶ�ض��Ķ���
	 * ����{contract}: ��Լ��Ϣ������������صĺ�Լ����
	 * ����{order}: ������Ϣ���������������͡��������۸��
	 * ����{orderState}: ����״̬�����������ĳɽ������ʣ�������
	 */
	void onResOpenOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState);

	/*
	 * ��ʾ������Ϣ�б�Ľ���
	 * �˺����ڽ��յ����ж�����Ϣ�󱻵��ã�����֪ͨӦ�ó��򶩵���Ϣ�б����
	 */
	void onResOpenOrderEnd();

	/*
	 * ���մ�����Ϣ
	 * ����{str}: ������Ϣ������
	 * ����{lastError}: ���һ�δ������
	 */
	void onResWinError(const std::string& str, int lastError);

	/*
	 * ���ӹر�ʱ����
	 * ����TWS�����ӹر�ʱ���˺��������ã���������ִ�������������������߼�
	 */
	void onResConnectionClosed();

	/*
	 * �����˻�ֵ����
	 * ����{key}: �˻�ֵ�ļ�������ʶ�˻����ض�����
	 * ����{val}: �˻�ֵ����ֵ����Ӧ�����ľ�����ֵ
	 * ����{currency}: �˻�ֵ�Ļ��ҵ�λ
	 * ����{accountName}: �˻����ƣ���ʶ�˻���������
	 */
	void onResUpdateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName);

	/*
	 * ����Ͷ����ϸ���
	 * ����{contract}: ��Լ��Ϣ������Ͷ�������֤ȯ����ϸ��Ϣ
	 * ����{position}: Ͷ�������֤ȯ�ĳֲ�����
	 * ����{marketPrice}: ֤ȯ���г��۸�
	 * ����{marketValue}: ֤ȯ���г���ֵ�����г��۸���Գֲ�����
	 * ����{averageCost}: ֤ȯ��ƽ���ɱ��۸�
	 * ����{unrealizedPNL}: δʵ��ӯ��������ǰ�г��۸���ƽ���ɱ�֮��Ĳ��
	 * ����{realizedPNL}: ʵ��ӯ������������֤ȯ��ӯ��
	 * ����{accountName}: �˻����ƣ���ʶ�˻���������
	 */
	void onResUpdatePortfolio(const Contract& contract, Decimal position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName);

	/*
	 * �����˻�ʱ�����
	 * ����{timeStamp}: �˻������µ�ʱ���
	 */
	void onResUpdateAccountTime(const std::string& timeStamp);

	/*
	 * �˻���Ϣ���ؽ���
	 * ���˻���Ϣ�������ʱ���ô˺���
	 * ����{accountName}: �˻����ƣ���ʶ�˻���������
	 */
	void onResAccountDownloadEnd(const std::string& accountName);

	/*
	 * ��һ����Ч����ID
	 * ���ͻ�����Ҫ�����¶���ʱ���˺���������һ�����õĶ���ID
	 * ����{orderId}: ��һ����Ч�Ķ���ID
	 */
	void onResNextValidId(OrderId orderId);

	/*
	 * ���պ�Լ��ϸ��Ϣ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�������
	 * ����{contractDetails}: ��Լ��ϸ��Ϣ��������Լ�ĸ�������
	 */
	void onResContractDetails(int reqId, const ContractDetails& contractDetails);

	/*
	 * ����ծȯ��Լ��ϸ��Ϣ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�������
	 * ����{contractDetails}: ծȯ��Լ��ϸ��Ϣ������ծȯ��Լ�ĸ�������
	 */
	void onResBondContractDetails(int reqId, const ContractDetails& contractDetails);

	/*
	 * ��Լ��ϸ��Ϣ�б����
	 * �����յ����к�Լ��ϸ��Ϣ����ô˺�������ʾ�б����
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�������
	 */
	void onResContractDetailsEnd(int reqId);

	/*
	 * ����ִ������
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�������
	 * ����{contract}: ��Լ��Ϣ������ִ��������صĺ�Լ����
	 * ����{execution}: ִ����Ϣ�����������ĳɽ�����
	 */
	void onResExecDetails(int reqId, const Contract& contract, const Execution& execution);

	/*
	 * ִ�������б����
	 * �����յ�����ִ���������ô˺�������ʾ�б����
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�������
	 */
	void onResExecDetailsEnd(int reqId);

	/*
	 * ���մ�����Ϣ
	 * ����{id}: ������Ϣ��ID�����ڱ�ʶ������Ϣ
	 * ����{errorCode}: ������룬�ṩ�������͵����ֱ�ʾ
	 * ����{errorString}: ������Ϣ���ı�����
	 * ����{advancedOrderRejectJson}: �߼������ܾ���JSON�ַ���������������ϸ��Ϣ
	 */
	void onResError(int id, int errorCode, const std::string& errorString, const std::string& advancedOrderRejectJson);

	/*
	 * �����г���ȸ���
	 * ����{id}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{position}: �г���ȵ�λ��
	 * ����{operation}: �������ͣ�����ӡ��޸Ļ�ɾ���г������
	 * ����{side}: ���׷��������
	 * ����{price}: �۸�
	 * ����{size}: �������Ĵ�С
	 */
	void onResUpdateMktDepth(TickerId id, int position, int operation, int side, double price, Decimal size);

	/*
	 * ����Level 2�г���ȸ���
	 * ����{id}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{position}: �г���ȵ�λ��
	 * ����{marketMaker}: �����̵ı�ʶ
	 * ����{operation}: �������ͣ�����ӡ��޸Ļ�ɾ���г������
	 * ����{side}: ���׷��������
	 * ����{price}: �۸�
	 * ����{size}: �������Ĵ�С
	 * ����{isSmartDepth}: �Ƿ��������г����
	 */
	void onResUpdateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation, int side, double price, Decimal size, bool isSmartDepth);

	/*
	 * �������Ź������
	 * ����{msgId}: ��ϢID�����ڱ�ʶ�ض������Ź���
	 * ����{msgType}: ��Ϣ���ͣ������š���������
	 * ����{newsMessage}: ���Ź������Ϣ����
	 * ����{originExch}: ���Ź������Դ������
	 */
	void onResUpdateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch);

	/*
	 * �����ܹ�����˻��б�
	 * ����{accountsList}: �ܹ�����˻��б��Զ��ŷָ����ַ���
	 */
	void onResManagedAccounts(const std::string& accountsList);

	/*
	 * ���ղ����������
	 * ����{pFaDataType}: ���������������
	 * ����{cxml}: ����������ݵ�CXML�ַ���
	 */
	void onResReceiveFA(faDataType pFaDataType, const std::string& cxml);

	/*
	 * ������ʷ���ݸ���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʷ��������
	 * ����{bar}: ������ʷ���ݵ�Bar����
	 */
	void onResHistoricalData(TickerId reqId, const Bar& bar);

	/*
	 * ��ʷ�����������
	 * ����ʷ�����������ʱ���ô˺���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʷ��������
	 * ����{startDateStr}: �������ʷ���ݵĿ�ʼ�����ַ���
	 * ����{endDateStr}: �������ʷ���ݵĽ��������ַ���
	 */
	void onResHistoricalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr);

	/*
	 * ����ɨ���ǲ���
	 * ����{xml}: ɨ���ǲ�����XML�ַ���
	 */
	void onResScannerParameters(const std::string& xml);

	/*
	 * ����ɨ�������ݸ���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض���ɨ��������
	 * ����{rank}: ɨ����������
	 * ����{contractDetails}: ��Լ��ϸ��Ϣ������ɨ�����еĺ�Լ����
	 * ����{distance}: ɨ�������ľ������
	 * ����{benchmark}: ��׼����
	 * ����{projection}: ͶӰ����
	 * ����{legsStr}: ��Ȩ�����ַ�����ʾ
	 */
	void onResScannerData(int reqId, int rank, const ContractDetails& contractDetails, const std::string& distance, const std::string& benchmark, const std::string& projection, const std::string& legsStr);

	/*
	 * ɨ���������������
	 * ��ɨ���������������ʱ���ô˺���
	 * ����{reqId}: ɨ��������ID
	 * ����{contractList}: ɨ���ǵõ��ĺ�Լ�б�
	 */
	void onResScannerDataEnd(int reqId, const std::vector<Contract>& contractList);

	/*
	 * ʵʱK�����ݸ���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض���ʵʱK����������
	 * ����{time}: K�ߵ�ʱ�����ͨ����K�߽�����ʱ��
	 * ����{open}: K�ߵĿ��̼�
	 * ����{high}: K�ߵ���߼�
	 * ����{low}: K�ߵ���ͼ�
	 * ����{close}: K�ߵ����̼�
	 * ����{volume}: K�ߵĳɽ���
	 * ����{wap}: K�ߵļ�Ȩƽ���۸�
	 * ����{count}: K���ڼ�Ľ��״���
	 */
	void onResRealtimeBar(TickerId reqId, long time, double open, double high, double low, double close, Decimal volume, Decimal wap, int count);

	/*
	 * ��ǰ������ʱ�����
	 * ����{time}: �������ĵ�ǰʱ���
	 */
	void onResCurrentTime(long time);

	/*
	 * ���������ݸ���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��Ļ�������������
	 * ����{data}: ���������ݵ��ַ�����ʾ
	 */
	void onResFundamentalData(TickerId reqId, const std::string& data);

	/*
	 * Delta������֤��Ϣ����
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض���Delta������֤����
	 * ����{deltaNeutralContract}: Delta���Ժ�Լ��Ϣ��������Լ��Delta/�۸�����
	 */
	void onResDeltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract);

	/*
	 * �г��������ݽ���
	 * ���г����������������ʱ���ô˺���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����г���������
	 */
	void onResTickSnapshotEnd(int reqId);

	/*
	 * �г��������͸���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����г�������������
	 * ����{marketDataType}: ��ǰ���г��������ͣ���ʵʱ����ʱ��
	 */
	void onResMarketDataType(TickerId reqId, int marketDataType);

	/*
	 * Ӷ�𱨸����
	 * ����{commissionReport}: Ӷ�𱨸���󣬰������׵�Ӷ������
	 */
	void onResCommissionReport(const CommissionReport& commissionReport);

	/*
	 * �ֲָ���
	 * ����{account}: �˻����ƣ���ʶ�˻���������
	 * ����{contract}: ��Լ���󣬰����ֲ���صĺ�Լ����
	 * ����{position}: �ֲ�����
	 * ����{avgCost}: ƽ���ɱ��۸�
	 */
	void onResPosition(const std::string& account, const Contract& contract, Decimal position, double avgCost);

	/*
	 * �ֲ��б����
	 * �����յ����гֲ���Ϣ����ô˺�������ʾ�ֲ��б����
	 */
	void onResPositionEnd(const std::vector<PositionData>& position);

	/*
	 * �˻�ժҪ����
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����˻�ժҪ����
	 * ����{account}: �˻����ƣ���ʶ�˻���������
	 * ����{tag}: ժҪ��ǩ����ʶժҪ���ض�����
	 * ����{value}: ժҪֵ����Ӧ��ǩ�ľ�����ֵ
	 * ����{curency}: ժҪֵ�Ļ��ҵ�λ
	 */
	void onResAccountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& currency);

	/*
	 * �˻�ժҪ�������
	 * ���˻�ժҪ�������ʱ���ô˺���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����˻�ժҪ����
	 */
	void onResAccountSummaryEnd(int reqId);

	/*
	 * API��Ϣ��֤��Ӧ
	 * ����{apiData}: ��API���յ�������
	 */
	void onResVerifyMessageAPI(const std::string& apiData);

	/*
	 * ��֤����¼�
	 * ����{isSuccessful}: ��֤�Ƿ�ɹ�
	 * ����{errorText}: �����֤ʧ�ܣ��ṩ������Ϣ���ı�
	 */
	void onResVerifyCompleted(bool isSuccessful, const std::string& errorText);

	/*
	 * ��ʾ�����б���Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʾ��������
	 * ����{groups}: �����б����ַ�����ʽ����
	 */
	void onResDisplayGroupList(int reqId, const std::string& groups);

	/*
	 * ��ʾ��������¼�
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʾ�����������
	 * ����{contractInfo}: ��Լ��Ϣ�ĸ���
	 */
	void onResDisplayGroupUpdated(int reqId, const std::string& contractInfo);

	/*
	 * API��Ϣ��֤����Ȩ��Ӧ
	 * ����{apiData}: ��API���յ�������
	 * ����{xyzChallange}: ��Ȩ��ս�ַ���
	 */
	void onResVerifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange);

	/*
	 * ��֤����Ȩ����¼�
	 * ����{isSuccessful}: ��֤����Ȩ�Ƿ�ɹ�
	 * ����{errorText}: �����֤����Ȩʧ�ܣ��ṩ������Ϣ���ı�
	 */
	void onResVerifyAndAuthCompleted(bool isSuccessful, const std::string& errorText);

	/*
	 * ����ȷ���¼�
	 * �˺����ڿͻ�����TWS��������������ʱ����
	 */
	void onResConnectAck();

	/*
	 * ���˻��ֲָ���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��Ķ��˻��ֲ�����
	 * ����{account}: �˻�����
	 * ����{modelCode}: ģ�ʹ���
	 * ����{contract}: ��Լ���󣬰����ֲ���صĺ�Լ����
	 * ����{pos}: �ֲ�����
	 * ����{avgCost}: ƽ���ɱ��۸�
	 */
	void onResPositionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, Decimal pos, double avgCost);

	/*
	 * ���˻��ֲ��б����
	 * �����յ����ж��˻��ֲ���Ϣ����ô˺�������ʾ�ֲ��б����
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��Ķ��˻��ֲ�����
	 */
	void onResPositionMultiEnd(int reqId);

	/*
	 * ���˻�����
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��Ķ��˻���������
	 * ����{account}: �˻�����
	 * ����{modelCode}: ģ�ʹ���
	 * ����{key}: �˻����Եļ�
	 * ����{value}: �˻����Ե�ֵ
	 * ����{currency}: �˻�����ֵ�Ļ��ҵ�λ
	 */
	void onResAccountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency);

	/*
	 * ���˻������б����
	 * �����յ����ж��˻�������Ϣ����ô˺�������ʾ�����б����
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��Ķ��˻���������
	 */
	void onResAccountUpdateMultiEnd(int reqId);

	/*
	 * ��Ȩ��Լ����������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����Ȩ��Լ��������
	 * ����{exchange}: ����������
	 * ����{underlyingConId}: ��ĺ�ԼID
	 * ����{tradingClass}: �������
	 * ����{multiplier}: ��Լ����
	 * ����{expirations}: ��Ȩ��Լ�ĵ����ռ���
	 * ����{strikes}: ��Ȩ��Լ��ִ�м۸񼯺�
	 */
	void onResSecurityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes);

	/*
	 * ��Ȩ��Լ�����������
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����Ȩ��Լ�����������
	 */
	void onResSecurityDefinitionOptionalParameterEnd(int reqId);

	/*
	 * ����Ԫ�ȼ���Ϣ��Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�������Ԫ�ȼ�����
	 * ����{tiers}: ����Ԫ�ȼ��б�
	 */
	void onResSoftDollarTiers(int reqId, const std::vector<SoftDollarTier>& tiers);

	/*
	 * ��������б���Ӧ
	 * ����{familyCodes}: ��������б�
	 */
	void onResFamilyCodes(const std::vector<FamilyCode>& familyCodes);

	/*
	 * ��Լ�����б���Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��ĺ�Լ��������
	 * ����{contractDescriptions}: ��Լ�����б�
	 */
	void onResSymbolSamples(int reqId, const std::vector<ContractDescription>& contractDescriptions);

	/*
	 * �г���Ƚ������б���Ӧ
	 * ����{depthMktDataDescriptions}: �г�������������б�
	 */
	void onResMktDepthExchanges(const std::vector<DepthMktDataDescription>& depthMktDataDescriptions);

	/*
	 * ����������Ӧ
	 * ����{tickerId}: ����ID
	 * ����{timeStamp}: ����ʱ���
	 * ����{providerCode}: �����ṩ�ߴ���
	 * ����{articleId}: ����ID
	 * ����{headline}: ͷ������
	 * ����{extraData}: ��������
	 */
	void onResTickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData);

	/*
	 * ���������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��������������
	 * ����{theMap}: �������ӳ��
	 */
	void onResSmartComponents(int reqId, const SmartComponentsMap& theMap);

	/*
	 * �������������Ӧ
	 * ����{tickerId}: ����ID
	 * ����{minTick}: ��С�۸�䶯��λ
	 * ����{bboExchange}: ��ѳ��ۺ�Ҫ�۵Ľ���������
	 * ����{snapshotPermissions}: ����Ȩ��
	 */
	void onResTickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions);

	/*
	 * �����ṩ���б���Ӧ
	 * ����{newsProviders}: �����ṩ���б�
	 */
	void onResNewsProviders(const std::vector<NewsProvider>& newsProviders);

	/*
	 * ����������Ӧ
	 * ����{requestId}: ����ID�����ڱ�ʶ�ض���������������
	 * ����{articleType}: ��������
	 * ����{articleText}: �����ı�
	 */
	void onResNewsArticle(int requestId, int articleType, const std::string& articleText);

	/*
	 * ��ʷ����������Ӧ
	 * ����{requestId}: ����ID�����ڱ�ʶ�ض�����ʷ������������
	 * ����{time}: ���ŷ�����ʱ��
	 * ����{providerCode}: �����ṩ�ߵĴ���
	 * ����{articleId}: ���µ�Ψһ��ʶ��
	 * ����{headline}: ���ŵı���
	 */
	void onResHistoricalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline);

	/*
	 * ��ʷ�������ݽ���
	 * ����{requestId}: ����ID�����ڱ�ʶ�ض�����ʷ������������
	 * ����{hasMore}: ָʾ�Ƿ��и������ʷ��������
	 */
	void onResHistoricalNewsEnd(int requestId, bool hasMore);

	/*
	 * �г�������ݵ�ʱ�����Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����г������������
	 * ����{headTimestamp}: �г�������ݵ�ʱ���
	 */
	void onResHeadTimestamp(int reqId, const std::string& headTimestamp);

	/*
	 * ֱ��ͼ������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض���ֱ��ͼ��������
	 * ����{data}: ֱ��ͼ��������
	 */
	void onResHistogramData(int reqId, const HistogramDataVector& data);

	/*
	 * ��ʷ���ݸ���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʷ��������
	 * ����{bar}: ������ʷ���ݵ�Bar����
	 */
	void onResHistoricalDataUpdate(TickerId reqId, const Bar& bar);

	/*
	 * �г����������ض���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����г���������
	 * ����{conid}: ��ԼID
	 * ����{exchange}: ����������
	 */
	void onResRerouteMktDataReq(int reqId, int conid, const std::string& exchange);

	/*
	 * �г���������ض���
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����г��������
	 * ����{conid}: ��ԼID
	 * ����{exchange}: ����������
	 */
	void onResRerouteMktDepthReq(int reqId, int conid, const std::string& exchange);

	/*
	 * �г�������Ӧ
	 * ����{marketRuleId}: �г�����ID
	 * ����{priceIncrements}: �۸�����������������ͬ�۸�ˮƽ�ļ۸񲽳�
	 */
	void onResMarketRule(int marketRuleId, const std::vector<PriceIncrement>& priceIncrements);

	/*
	 * ӯ����Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض���ӯ������
	 * ����{dailyPnL}: ��ӯ��
	 * ����{unrealizedPnL}: δʵ��ӯ��
	 * ����{realizedPnL}: ʵ��ӯ��
	 */
	void onResPnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL);

	/*
	 * ��һ�ֲ�ӯ����Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��ĵ�һ�ֲ�ӯ������
	 * ����{pos}: �ֲ�����
	 * ����{dailyPnL}: ��ӯ��
	 * ����{unrealizedPnL}: δʵ��ӯ��
	 * ����{realizedPnL}: ʵ��ӯ��
	 * ����{value}: �ֲֵ��ܼ�ֵ
	 */
	void onResPnlSingle(int reqId, Decimal pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value);

	/*
	 * ��ʷ�ɽ��۸���Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʷ�ɽ��۸�����
	 * ����{ticks}: �ɽ��۸������
	 * ����{done}: ָʾ�Ƿ������������ʷ���ݵķ���
	 */
	void onResHistoricalTicks(int reqId, const std::vector<HistoricalTick>& ticks, bool done);

	/*
	 * ��ʷ����������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʷ������������
	 * ����{ticks}: �������۵�����
	 * ����{done}: ָʾ�Ƿ������������ʷ���ݵķ���
	 */
	void onResHistoricalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done);

	/*
	 * ��ʷ���ɽ��۸���Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʷ���ɽ��۸�����
	 * ����{ticks}: ���ɽ��۸������
	 * ����{done}: ָʾ�Ƿ������������ʷ���ݵķ���
	 */
	void onResHistoricalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done);

	/*
	 * ��ʳɽ�������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʳɽ���������
	 * ����{tickType}: �ɽ�����
	 * ����{time}: �ɽ�ʱ���ʱ���
	 * ����{price}: �ɽ��۸�
	 * ����{size}: �ɽ�����
	 * ����{tickAttribLast}: �ɽ�����
	 * ����{exchange}: �ɽ��Ľ�����
	 * ����{specialConditions}: ��������
	 */
	void onResTickByTickAllLast(int reqId, int tickType, time_t time, double price, Decimal size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions);

	/*
	 * �����������������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����������������������
	 * ����{time}: ����ʱ���ʱ���
	 * ����{bidPrice}: ���
	 * ����{askPrice}: ����
	 * ����{bidSize}: ����
	 * ����{askSize}: ����
	 * ����{tickAttribBidAsk}: ������������
	 */
	void onResTickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, Decimal bidSize, Decimal askSize, const TickAttribBidAsk& tickAttribBidAsk);

	/*
	 * ����м��������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�������м����������
	 * ����{time}: �м��ʱ���ʱ���
	 * ����{midPoint}: �м��
	 */
	void onResTickByTickMidPoint(int reqId, time_t time, double midPoint);

	/*
	 * ��������Ӧ
	 * ����{orderId}: ����ID
	 * ����{apiClientId}: API�ͻ���ID
	 * ����{apiOrderId}: API����ID
	 */
	void onResOrderBound(long long orderId, int apiClientId, int apiOrderId);

	/*
	 * ��ɵĶ�����Ӧ
	 * ����{contract}: ��Լ����
	 * ����{order}: ��������
	 * ����{orderState}: ����״̬����
	 */
	void onResCompletedOrder(const Contract& contract, const Order& order, const OrderState& orderState);

	/*
	 * ��ɵĶ����б����
	 * �˺�����������ɵĶ������ݷ�����Ϻ����
	 */
	void onResCompletedOrdersEnd();

	/*
	 * �滻FA�˻�������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض���FA�˻��滻����
	 * ����{text}: �滻�������ı�����
	 */
	void onResReplaceFAEnd(int reqId, const std::string& text);

	/*
	 * ����վԪ������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��Ĺ���վԪ��������
	 * ����{dataJson}: Ԫ���ݵ�JSON�ַ���
	 */
	void onResWshMetaData(int reqId, const std::string& dataJson);

	/*
	 * ����վ�¼�������Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض��Ĺ���վ�¼���������
	 * ����{dataJson}: �¼����ݵ�JSON�ַ���
	 */
	void onResWshEventData(int reqId, const std::string& dataJson);

	/*
	 * ��ʷ����ʱ�����Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض�����ʷ����ʱ�������
	 * ����{startDateTime}: ��ʼ���ں�ʱ��
	 * ����{endDateTime}: �������ں�ʱ��
	 * ����{timeZone}: ʱ��
	 * ����{sessions}: ���׻Ự������
	 */
	void onResHistoricalSchedule(int reqId, const std::string& startDateTime, const std::string& endDateTime, const std::string& timeZone, const std::vector<HistoricalSession>& sessions);

	/*
	 * �û���Ϣ��Ӧ
	 * ����{reqId}: ����ID�����ڱ�ʶ�ض����û���Ϣ����
	 * ����{whiteBrandingId}: �ױ�ID������ʶ���û�
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
