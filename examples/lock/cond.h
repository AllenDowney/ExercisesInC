
typedef pthread_cond_t Cond;

Cond *make_cond ();
void cond_wait (Cond *cond, pthread_mutex_t *pmutex);
void cond_signal (Cond *cond);
