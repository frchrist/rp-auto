#ifndef INDEXERENTITY_H
#define INDEXERENTITY_H

class IndexerEntity;

class IndexerEntity
{
public:
    explicit IndexerEntity();
    enum class STATE{
        UNINDEXED = 0X01,
        INDEXED = 0X02
    };

    enum class WHY{
        NO_REASON,
        FIRST_LOADED,
        NOT_INDEXABLE,
        BANK_UNRECORD_IT,
        ENTREPRISE_UNRECORD_IT,
        ENTREPRISE_RECORED_IT_WRONG,
        BANK_RECORD_IT_WRONG
    };
    explicit IndexerEntity(int id, IndexerEntity::STATE state, IndexerEntity::WHY reason);

    STATE getState() const;
    WHY getReason() const;

    void setState(STATE newState);
    void setReason(WHY newReason);
    bool isIndexed(){
        return _state == STATE::INDEXED;
    }

    int id() const;
    void setId(int newId);

private:
    int _id;
    STATE _state;
    WHY _reason;
};

#endif // INDEXERENTITY_H
