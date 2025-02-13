# Unity Installation and AR Project Guide

This guide provides step-by-step instructions for installing Unity and setting it up for an Augmented Reality (AR) project.

---

## Prerequisites
- **Unity Hub**: A central platform to install and manage Unity versions and projects.
- **Unity Editor**: A version of Unity compatible with AR development.
- **AR Foundation Package**: Unity's package for building AR applications.
- **Supported Hardware**: A device capable of running AR applications (e.g., Android or iOS device).
- **Internet Access**: Required for downloading Unity components and packages.

---

## Installation Steps

### 1. Download Unity Hub
- Visit the official Unity website and download Unity Hub:
  [Unity Hub Download](https://unity.com/download)

### 2. Install Unity Editor
1. Open Unity Hub after installation.
2. Go to the **Installs** tab and click **Add**.
3. Select a version of Unity compatible with AR Foundation (e.g., Unity 2020.3 or later).
4. Include the following modules during installation:
   - **Android Build Support** (if targeting Android devices)
   - **iOS Build Support** (if targeting iOS devices)

### 3. Create a New Project
1. Open Unity Hub.
2. Go to the **Projects** tab and click **New Project**.
3. Choose the **3D (URP)** template for better graphics or **3D Core** for basic projects.
4. Name your project and select a save location, then click **Create**.

### 4. Install AR Foundation Package
1. Open Unity and go to **Window > Package Manager**.
2. Search for **AR Foundation** in the Unity Registry.
3. Install the latest version of AR Foundation.
4. (Optional) Depending on your device, also install **ARKit XR Plugin** (for iOS) or **ARCore XR Plugin** (for Android).

---

## Setting Up the AR Project

### 1. Configure the Project Settings
- Go to **Edit > Project Settings > Player**:
  - For Android: Set the minimum API level to 24 or higher.
  - For iOS: Enable ARKit in the XR settings.

### 2. Create an AR Scene
1. Delete the default **Main Camera** in the scene.
2. Add an **AR Session Origin** and **AR Session** from the AR Foundation package.
3. Attach an **AR Camera** to the AR Session Origin.

### 3. Build and Deploy the Project
1. Go to **File > Build Settings**.
2. Choose your target platform (Android or iOS) and click **Switch Platform**.
3. Connect your device and ensure Developer Mode is enabled.
4. Click **Build and Run** to deploy the app to your device.

---

## Notes
1. **Unity License**
   - A free Unity Personal license is sufficient for non-commercial projects.
   - Visit [Unity Licensing](https://unity.com/unity-licenses) for more details.

2. **AR Device Compatibility**
   - Ensure your device supports ARKit (iOS) or ARCore (Android).

3. **Additional Resources**
   - Unity Learn: [Introduction to AR](https://learn.unity.com/)
   - Official Unity Documentation: [AR Foundation](https://docs.unity3d.com/Packages/com.unity.xr.arfoundation@latest)

---

If you encounter any issues during setup or development, refer to the [Unity Forums](https://forum.unity.com/) or the [Unity Support Page](https://support.unity.com/).
