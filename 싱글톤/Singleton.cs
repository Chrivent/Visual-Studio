using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Singleton<T> : MonoBehaviour where T: MonoBehaviour
{
    protected static T _instance;

    protected static object _lock = new object();

    public static T Instance
    {
        get
        {
            if(applicationIsQutting)
            {
                return null;
            }

            lock (_lock)
            {
                if(_instance == null)
                {
                    _instance = (T)FindObjectOfType(typeof(T));

                    if(FindObjectOfType(typeof(T)).Length > 1)
                    {
                        return _instance;
                    }

                    if(_instance == null)
                    {
                        GameObject singleton = new GameObject();
                        _instance = singleton.AddComponent<T>();
                        singleton.name = "(singleton)" + typeof(T).ToString();

                        DontDestroyOnLoad(singleton);
                    }
                    else
                    {

                    }
                }

                return _instance;
            }
        }
    }

    private static bool applicationIsQutting = false;
    protected virtual void OnDestroy()
    {
        applicationIsQutting = true;
        _lock = null;

        if(_instance == this)
            _instance = null;
    }
}
