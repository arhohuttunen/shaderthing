#include <QTextStream>
#include "shaderlanguagehighlighter.h"

ShaderLanguageHighlighter::ShaderLanguageHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    QFile file(":/glsl/keywords.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString contents = file.readAll();

    QStringList keywords = contents.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    foreach (const QString &keyword, keywords)
    {
        rule.pattern = QRegExp("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
}

void ShaderLanguageHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}
