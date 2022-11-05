using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarController : MonoBehaviour
{
    private void Start()
    {
        AudioManager.Instance.PlayCarSFX();
    }
}
