#ifndef SHADERLANGUAGEHIGHLIGHTER_H
#define SHADERLANGUAGEHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>

class ShaderLanguageHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    ShaderLanguageHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
};

#endif // SHADERLANGUAGEHIGHLIGHTER_H
