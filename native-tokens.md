We have these two ByteStrings that define a coin, or, as it is also called, an asset class.

```
assetClass :: CurrencySymbol -> TokenName -> AssetClass
assetClass s t = AssetClass (s, t)
```

-> Ada is one asset class, and custom native tokens will be other asset classes.

