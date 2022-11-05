using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class AudioManager : Singleton<AudioManager>
{
    AudioSource audioSource;

    AudioClip carSFX;

    private void Awake()
    {
        audioSource = GetComponent<AudioSource>();

        carSFX = Resources.Load<AudioClip>("car_se");
    }

    public void PlaySound(AudioClip clip)
    {
        audioSource.PlayOneShot(clip);
    }

    public void PlayCarSFX()
    {
        PlaySound(carSFX);
    }
}