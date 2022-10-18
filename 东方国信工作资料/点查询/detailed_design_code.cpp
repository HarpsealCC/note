/*** 
 * @FilePath: /github/harpseal/东方国信工作资料/点查询/detailed_design_code.cpp
 * @Author: harpseal
 * @Date: 2022-07-18 16:39:49
 * @LastEditTime: 2022-08-01 11:07:25
 * @email: 844291270@qq.com
 */

#include <iostream>

void GenerateDPFilterKey(Model::INode *nodes,
 xcloud::TupleDesc* td, std::vector<DPFilterKey> dpfilterkey_list) {
    DPFilterKey tmp;
    // 先判断是否是is null 或 is not null操作
    if (NODE_TYPE_IS_NULL_EXP_NODE == node->GetNodeType()) {  
        tmp. filter_col_id_ = GetColId(td, node)
        tmp.isnull = node -> GetNull
    } else if (NODE_TYPE_OPERATOR == node->GetNodeType()) {
        // 再判断是否是and操作，如果是，需要递归调用
        if (Model::OP_AND == node->getOperatorValue()) {
            lt = node->getleftnode()
            rt = node->getrighttnode()
            GenerateDPFilterKey(lt, td, dpfilterkey_list);
            GenerateDPFilterKey(rt, td, dpfilterkey_list);
        // 是否是 = <= >= < > in between，如果是，为DPFilterKey赋值
        } else if (node->getOperatorValue() <= Model::OP_IN) {
            tmp.filter_col_id_ = GetColId(td, node)
            tmp.op_and_value_.insert<OperatorValue, vector<INode*>>(
                node->getOperatorValue(), node->getValue()
            )
        }
    }
 }

void GenerateDPFilterKeys(std::vector<Model::INode*> *nodes,
 xcloud::TupleDesc* td, std::vector<DPFilterKey> dpfilterkey_list) {
    for (auto node : nodes) {
        GenerateDPFilterKey(node, td, dpfilterkey_list);
    }
 }


class DPFilterKey {
bool DoFilterOptimization() {
    // 如果有等值条件，and 连接的等值有两个以上且不相等就是非法
    auto eq_filter = op_and_value_.find(Model::OP_EQUAL);
    if (eq_filter.second().size() > 1) {
        for (i = 1 ;i < size; i++) {
            if (eq_filter.front() != eq_filter.second()[i]) {
                return false;
            }
        }
        // 最后将多个等值合并为1个值
    }
    auto in_filter = op_and_value_.find(Model::OP_IN);
    if (in_filter.second().size() > 1) {
        for (i = 1 ;i < size; i++) {
            // 判断有无交集
            if (in_filter.front() & eq_filter.second()[i]) {
                // 无交集
                return false;
            } else {
                // 将相交的部分记录下来，作为下次判断的依据
            }
        }
    }
    // （大于、大于等于）和（小于、小于等于）分别取交集，大取最大，小取最小
    auto in_filter = op_and_value_.find(Model::OP_LOWER_THAN);
    if () {  // 无交集
        return false;
    } else {  // 取到交集
        // 需要再和等值结果进行比较，有交集取交集，无交集return false；
    }
}
};

class MinMaxRowGroupFilter {
bool NeedDoFilter(int rg_id) {
    rowgroup = file_meta_data_.rowgroup[rg_id];
    check(rowgroup)  // 如果获取失败，预计抛异常处理
    // 如果没有minmax，或者有其他全局变量控制，可以认为不需要做过滤
    if (!rowgroup.minmax || GFlag) {
        return false;
    } else {
        return true;
    }
}
bool RowGroupFilterProcess(int rg_id) {
    rowgroup = file_meta_data_.rowgroup[rg_id];
    check(rowgroup)  // 如果获取失败，预计抛异常处理
    pair<string,string> min_max = rowgroup.mixmax
    //  遍历过滤条件
    for (auto filter : dpfilterkey_list_) {
        if (isneedfilter) {
            // 调用helper，做具体类型的比较操作。
            isneedfilter = MinMaxFilterHelper::ProcessMinMaxFilter(min_max, filter);           
        } else {
            // 如果有某个条件被验证不要被过滤，直接break
            break;
        }
    }
    return isneedfilter;
}
}

class DictRowGroupFilter {
bool NeedDoFilter(int rg_id) {
    rowgroup = file_meta_data_.rowgroup[rg_id];
    check(rowgroup)  // 如果获取失败，预计抛异常处理
    // 数据页不是全部使用字典编码 ，或者有其他全局变量控制，可以认为不需要做过滤
    if (IsDictionaryEncoded(col_metadata) && GFlag) {
        return false;
    } else {
        return true;
    }
}

void GetDictInfoFromDecoder(int rg_id) {
    dict_vec_ = colscanner_->GetDictData(rg_id);
}
bool IsNeedFilterByDict(DPFilterKey filter) {
    for (auto value : filter.op_and_value_) {
        
    }
}

bool RowGroupFilterProcess(int rg_id) {
    rowgroup = file_meta_data_.rowgroup[rg_id];
    check(rowgroup)  // 如果获取失败，预计抛异常处理
    //  遍历过滤条件
    for (auto filter : dpfilterkey_list_) {
        if (isneedfilter) {
            // 判断过滤条件是否存在于字典页中
            isneedfilter = IsNeedFilterByDict(filter);           
        } else {
            // 如果有某个条件被验证不要被过滤，直接break
            break;
        }
    }
    return isneedfilter;
}
}

class IPageFilter {
std::vector<Parquet::PageIndex> GetPageIndexByValidRow(const vector<pair<int, int>>& valid_rownum_range) {
    std::vector<Parquet::PageIndex> page_index_list ;
    // valid_rownum_range 与 column_metadata_.row_index中的数据应该都是递增的
    auto index = column_metadata_.first_page_row_index;
    int start_id, end_id;
    for (auto range : valid_rownum_range) {
        if (range.first > index.end_row) {
            index.next;
        } else {
            start_id = index.id;  // 记录开始id
            if (range.second > index.end_row) {
                end_id = index.id  // 记录结束id
            }
        }
    }
    for (int i = start_id; i < end_id; i ++) {
        page_index_list.push_back(column_metadata_.index[i])
    }
}
} 

class NullPageFilter {
void PageFilterProcess(vector<pair<int, int>>& valid_rownum_range) {
    // 根据之前列过滤的有效row range获取本次过滤所要查询的page list
    page_index_list = GetPageIndexByValidRow(valid_rownum_range);
    // 获取page的row index
    for (auto page_index : page_index_list) {
        if (page_index.has_null) {
            pair<int,int> start_end_row_each_page = page_index.start_end;
            valid_rownum_range.push_back(start_end_row_each_page);
        }
    }
}

Bool NeedDoFilter() {
    if (dpfilterkey.isnull && GFlag)
}
}

class MixMaxPageFilter {
void PageFilterProcess(vector<pair<int, int>>& valid_rownum_range) {
    // 根据之前列过滤的有效row range获取本次过滤所要查询的page list
    page_index_list = GetPageIndexByValidRow(valid_rownum_range);
    valid_rownum_range.clear()
    for (auto page_index : page_index_list) {
        pair<string, string> min_max = page_index.min_max
        if (!MinMaxFilterHelper::ProcessMinMaxFilter(min_max, dpfilterkey)) {
            pair<int,int> start_end_row_each_page = page_index.start_end;
            valid_rownum_range.push_back(start_end_row_each_page);
        }
    }
}   
}
class MinMaxFilterHelper {
MinMaxFilterFunctor GetCompareFunc(DataType data_type, OPType op_type) {
    CompareFuncGenerater func_genrator = CompareFuncGenerater(op_type);
    return func_genrator.GernaratCompareFunc(data_type);
}

bool ProcessMinMaxFilter(pair<string,string> min_max, DPFilterKey* filterkey) {
    bool if_do_filter = false
    for (auto iter : filterkey.op_and_value_) {
        switch(iter.op_type) {
            case eq:
                // node value 小于最小 || 大于最大
                lt_func = func_generater_.GernaratCompareFunc(lt,
                        iter.getvaluenode().DataType());
                gt_func = func_generater_.GernaratCompareFunc(gt,
                        iter.getvaluenode().DataType())
                if (lt_func(min,iter.getvaluenode()) || gt_func(max,iter.getvaluenode())) {
                    if_do_filter = true;
                }
            break;
            case lt:
                // node value 小于最小
                lt_func = func_generater_.GernaratCompareFunc(lt,
                        iter.getvaluenode().DataType());
                if (lt_func(min,iter.getvaluenode())) {
                    if_do_filter = true;
                }
            break;
            case gt:
                // node value 大于最大
                gt_func = func_generater_.GernaratCompareFunc(gt,
                        iter.getvaluenode().DataType())
                if (gt_func(max,iter.getvaluenode())) {
                    if_do_filter = true;
                }           
        }
    }
}

}
class CompareFuncGenerater {

public:
    CompareFuncGenerater(OPType op_type) {
    }
template<class T>
MinMaxFilterFunctor FuncGenerater(OPType type) {
    switch(type) {
        case EQ:
            return boost::bind(CompareEq<T>, _1, _2);
        case LT:
            return boost::bind(CompareLt<T>, _1, _2);
        case GT:
            return boost::bind(CompareGt<T>, _1, _2);
        default:
            break;
    }
}


MinMaxFilterFunctor GernaratCompareFunc(OPType op_type, DataType data_type) {
    switch (data_type)
    {
    case Model::DATA_INT:
        return FuncGenerater<int>(op_type);
    case Model::DATA_DOUBLE:
        return FuncGenerater<double>(op_type);
    ...
    default:
        break;
    }
}
template<class A>
bool Comparelt(std::string value, INode* nodevalue) {
    A min_or_max;
    parquet::StringToValue(value, min_or_max);
    if (min_or_max < nodevalue.GetValue<A>()) {
        return true;
    } else {
        return false;
    }
}
}

class DataPackScanner {
bool DataPackScanner::internal_open() {
    // open file meta data
    // 依次是null minmax bloom dict 
    std::vector<int> rg_ids_before;   // 过滤前的rowgoup id 列表
    std::vector<int> rg_ids_after;      // 过滤后的rowgoup id 列表
    for (auto i : rg_ids_before) {    // 每个rowgroup
        bool need_filter = false;
        for (auto iter : rowgroup_filter_list) {  // 每个过滤器
            if (iter->NeedDoFilter(i)) {
                if (iter->RowGroupFilterProcess(i)) {
                    need_filter = true;  // 如果当前rowgroup被过滤，就不用继续了
                    break;
                }
            }
        }
        if (!need_filter) {
            rg_ids_after.push_back(i);
        }
    }
}
bool GenerateRowgroupFilter(std::vecter<std::unique_ptr<IRowGroupFilter>> filter_list) {
     // 依次是null minmax bloom dict 
     for(...) { 
        if (GFLag) {  // 如果有全局参数控制
            std::unique_ptr<IRowGroupFilter> filer;
            filer.reset(CreateRowGroupFilter())
            filter_list.push_back(filer)
        }
     }
    return ret;
}
}


class ParquetFileScanner {
Void GenerateVaildPageRange(
    const vector<pair<int,int>>& vaild_row_range,
    parquet::ColumnMetaData* col_md,
    ValidPageRange&  vaild_page_range) {
    auto iter_vaild_row_begin = vaild_row_range.begin();
    auto iter_vaild_row_end = vaild_row_range.end();

    auto iter_page_row_index_begin = col_md.rowindex.begin();
    auto iter_page_row_index_end = col_md.rowindex.end();
    // vaild_row_range与column中存的page row index都为递增的
    for (; iter_vaild_row_begin != iter_vaild_row_end; ) {
        if (!do_row_end_judge) {  // start row id 判断
            if (iter_vaild_row_begin.first > iter_page_row_index_begin.endrowid) {
                iter_page_row_index_begin++;
                continue;
            } else {
                start_row_id = iter_page_row_index_begin.startrowid;
                do_row_end_judge = true;
            }
        } else {  // end row id 判断
            if (iter_vaild_row_begin.end > iter_page_row_index_begin.endrowid) {
                iter_page_row_index_begin++;
                continue;
            } else {
                end_row_id = iter_page_row_index_begin.endrowid;
                iter_vaild_row_begin++  // 下一个判定区间
                do_row_end_judge = false
                iter_page_row_index_begin++
                continue;
            }
        }
        vaild_page_range.push_back(start_row_id,end_row_id);
    }
}


Void CalSkipAndReadRange(const ValidPageRangeIndex  vaild_row_index,
        const pair<int,int> vaild_page_range,  
        int & skip_rows_front , int & req_rows,int & skip_rows_behind) {
    skip_rows_front = valid_range_index.first - vaild_row_index.page_index_of_startrowid_;
    req_rows = vaild_row_index.page_index_of_endrowid_ -
            vaild_row_index.page_index_of_startrowid_;
    skip_rows_behind = vaild_page_range.second - vaild_row_index.page_index_of_endrowid_;
}

vector<std::pair<int64_t, int64_t>> GetColRange(
        const RowGroup & rowGroup, int idx,
        vector<vector<int>> value_page_index, bool if_cache_dict) {
    colMD = rowGroup.colMD[idx];
    vector<std::pair<int64_t, int64_t>> ret;
    if (!if_cache_dict) {  // 如果没有进行字典页的缓存
        ret.push_back(colMD.dictionary_page_offset, colMD.dictionary_page_len);
    }
    // value_page_index  连续的有效页id存放在一起，按一个pair进行add range
    for (auto vec : value_page_index) {
        int64_t offset= colMD.pageindex[vec.front()].pageOffset;
        int64_t col;
        for (auto i : vec) {  // 相邻的page的offset进行累加
            col += colMD.pageindex[i].pageSize
        }
        ret.push_back(offset,col);
    }
}

bool GeneratePageFilter(std::vecter<std::unique_ptr<IPageFilter>>& filter_list) {
    // null  min max filter
     for(...) { 
        if (GFLag) {  // 如果有全局参数控制
            std::unique_ptr<IPageFilter> filer;
            filer.reset(CreatePageFilter())
            filter_list.push_back(filer)
        }
     }
    return ret;
}

void ParquetFileScanner::openColAgent(ColumnScannerAgent & agent,
        const std::vector<RowGroup> & rowGroups) {
    // 之前逻辑保持一致
    GeneratePageFilter(filter_list);
    vector<pair<int, int>> filter_result
    vector<std::pair<int64_t, int64_t>> add_range;
    for (auto rgid : rg_list) {
        for (auto iter : filter_list) {
            if (iter->NeedDoFilter()) {
                iter->PageFilterProcess(filter_result);
            } 
        }
        GenerateVaildPageRange(filter_result, colmd, ValidPageRange);
        add_range = GetColRange();
        stream_addrange(add_range)
    }
    // 之后逻辑保持一致
}
void ParquetFileScanner::modifyColAgent(ColumnScannerAgent & agent,
                FS_MDP * mdp,const std::vector<int> &filterIndex, int requestRowNum) {
    if (after_page_filter) {
        need_read_num = mdp->get_row_count();   // mdp的行数才是需要实际读取的行数
        while (need_read_num > 0) {
            int skip_front, skip_behind;
            auto iter = agent.ValidPageRange.front();
            // 按照每个valid page range计算属于此range的filterIndex
            CalSkipAndReadRange(agent.ValidPageRange,
                skip_front,read_rows, skip_behind,filterIndex);
            if (skip_front > 0) {
                agent.reader->skip(skip_front);
            }
            if (read_rows > 0) {
                // iter.vaildvaluenum为计算之后的需要读取的有效行数
                readRowNum = agent.reader->getColumnData(mdp, agent.index, iter.vaildvaluenum, filterIndex);
                need_read_num -= readRowNum;
            }
            if (skip_behind > 0) {
                agent.reader->skip(skip_behind);
            }
        }
        if (need_read_num != 0) {
            throw "Rows Scanned is different from request. SCANNER ERROR"
        }
    }
    // 其他逻辑
}

}

class BaseColumnScanner {
void InitDictionary(PhyLayer::IScanStream * stream,
        const parquet::ColumnChunk* colChunk, const int rg_id) {
    // 按原有的逻辑读取字典页数据，并且构建解码器
    loadDictPage(m_DictPageBuf, BufSize);
    buildDictDecoder(m_DictPageBuf, BufSize);

    // 将解码器缓存
    dict_decoder_map_.insert(rg_id, dictdecoder);
    dict_page_buf_.insert(rg_id, m_DictPageBuf);
}

void reset(PhyLayer::IScanStream * stream,
        const parquet::ColumnChunk* colChunk, const int rg_id) {
    if (!dict_decoder_map_.count(rg_id)) {
        InitDictionary();
    }
    m_DictDecoder = dict_decoder_map_[rg_id];
    // 其余逻辑不变
}

bool IsCacheDictData(const int rg_id) {
    return dict_decoder_map_.count(rg_id);
}


}

class DictDecoder {
Bool DoDictFilter(IRowGroupFilter* filter) {
    for (auto dict : dict_) {

        if (filter.value_op.size() == 1) {
            // 单独条件只要满足就可以返回
            switch (op) {
                case eq:
                    if (dict == filter.value) {
                        return false;
                    }
                case lt:
                ...
            }
        } else {
            // 区间条件需要有值同时满足才可以返回
            bool if_do_filter = true;
            for (auto filter : filter.value_op) {
                switch (op) {
                    
                }
            }
        }
    }            
}
}

