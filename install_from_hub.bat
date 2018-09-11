mkdir "%appdata%\Mathematica\Applications\BIGParserAndMerger"
mkdir "%appdata%\Mathematica\Applications\cache"

certutil -urlcache -split -f "https://raw.githubusercontent.com/lllamnyp/BIGParserAndMerger/master/BIGParserAndMerger.m" "%appdata%\Mathematica\Applications\BIGParserAndMerger\BIGParserAndMerger.m"
certutil -urlcache -split -f "https://raw.githubusercontent.com/lllamnyp/BIGParserAndMerger/master/init.m" "%appdata%\Mathematica\Applications\BIGParserAndMerger\init.m"
certutil -urlcache -split -f "https://raw.githubusercontent.com/lllamnyp/BIGParserAndMerger/master/scandir.exe" "%appdata%\Mathematica\Applications\BIGParserAndMerger\scandir.exe"