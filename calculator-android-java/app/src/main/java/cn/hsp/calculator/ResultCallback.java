package cn.hsp.calculator;

import org.jetbrains.annotations.NotNull;

public interface ResultCallback {
    void updateResult(@NotNull String paramString);
}
