#ifndef GENDERDELEGATE_H
#define GENDERDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>


//性别复选框
class GenderDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit GenderDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    // 创建一个 QComboBox 作为性别编辑器
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const override
    {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItem("男");
        comboBox->addItem("女");
        return comboBox;
    }

    // 将当前单元格的数据设置到 QComboBox 上
    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox) {
            int idx = comboBox->findText(value); // 查找当前值在 ComboBox 中的索引
            if (idx >= 0) {
                comboBox->setCurrentIndex(idx);  // 设置 ComboBox 的当前项
            }
        }
    }

    // 将 QComboBox 的值设置到模型中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox) {
            model->setData(index, comboBox->currentText(), Qt::EditRole); // 将 ComboBox 的当前文本设置到模型中
        }
    }

    // 更新编辑器的显示区域
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const override
    {
        editor->setGeometry(option.rect); // 设置编辑器的位置和大小
    }
};

#endif // GENDERDELEGATE_H
