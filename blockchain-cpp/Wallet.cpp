#include "Wallet.h"

Wallet::Wallet() {
    generateKeyPair();
}

int Wallet::generateKeyPair() {
    EVP_PKEY_CTX* ctx;

    int ret = 1;
    BIO* bio_private = BIO_new_file("private_new.pem", "w+");
    BIO* bio_public = BIO_new_file("public_new.pem", "w+");
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
    if (ctx == NULL)
        goto err;
    if (EVP_PKEY_keygen_init(ctx) <= 0)
        goto err;
    if (EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_X9_62_prime256v1) <= 0)
        goto err;

    /* Generate key */
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
        goto err;
    StringUtil::printfGreen("Generate keypair successfully!\n");
    // write rsa private key to file

    ret = PEM_write_bio_PrivateKey(bio_private, pkey, NULL, NULL, 0, NULL, NULL);
    BIO_flush(bio_private);

    ret = PEM_write_bio_PUBKEY(bio_public, pkey);
    BIO_flush(bio_public);
    ret = 0;
    StringUtil::printfGreen("PublicKey:\n");
    StringUtil::printfGreen(StringUtil::publicKeyToString(pkey) + "\n");
    StringUtil::printfGreen("PrivateKey:\n");
    StringUtil::printfGreen(StringUtil::privateKeyToString(pkey) + "\n");
err:
    EVP_PKEY_CTX_free(ctx);
    return ret;
}
