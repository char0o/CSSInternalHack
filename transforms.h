bool WorldToScreen(const Vector& vecOrigin, Vector& vecScreen, float* pflViewMatrix)
{
    vecScreen[0] = pflViewMatrix[0] * vecOrigin[0] + pflViewMatrix[1] * vecOrigin[1] + pflViewMatrix[2] * vecOrigin[2] + pflViewMatrix[3];
    vecScreen[1] = pflViewMatrix[4] * vecOrigin[0] + pflViewMatrix[5] * vecOrigin[1] + pflViewMatrix[6] * vecOrigin[2] + pflViewMatrix[7];

    auto flTemp = pflViewMatrix[12] * vecOrigin[0] + pflViewMatrix[13] * vecOrigin[1] + pflViewMatrix[14] * vecOrigin[2] + pflViewMatrix[15];

    if (flTemp < 0.01f)
        return false;

    auto invFlTemp = 1.f / flTemp;
    vecScreen[0] *= invFlTemp;
    vecScreen[1] *= invFlTemp;

    static int iResolution[2] = { 0 };
    if (!iResolution[0] || !iResolution[1])
    {
        iResolution[0] = Overlay::COverlay::GetInstance()->GetWidth();
        iResolution[1] = Overlay::COverlay::GetInstance()->GetHeight();
    }

    auto x = (float)iResolution[0] / 2.f;
    auto y = (float)iResolution[1] / 2.f;

    x += 0.5f * vecScreen[0] * (float)iResolution[0] + 0.5f;
    y -= 0.5f * vecScreen[1] * (float)iResolution[1] + 0.5f;

    vecScreen[0] = x;
    vecScreen[1] = y;

    return true;
}